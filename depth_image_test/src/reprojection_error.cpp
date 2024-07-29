#include "functions_and_libs.h"

/*========================================================================================================================================
        The function returns the reprojection error using the Pose Matrix, 3D world points from Tiangulation and 2D points
                                from the epipolar class that returns the inliers.
==========================================================================================================================================*/

std::vector<cv::Point2f> create_2D_points_from_3D(const cv::Mat& pose, const std::vector<cv::Point3f>& pts3D){

    // Containers used in function
    cv::Mat pts3D_H(4, pts3D.size(), CV_64F);           // Empty 4D matrix for 3D homogeneous coordinates
    cv::Mat pts2D_H;                                    // Empty 3D matrix for 2D homogeneous coordinates
    std::vector<cv::Point2f> pts2D_H_N;                 // Normalised 3D matrix for 2D homogeneous coordinates
    double tempError, relativeError = 0.0;              // To store the temporary error and error

    // Construct 2D points from 3D points and Pose matrix
    // Step 1: convert 3D points to homogeneous coordinates  
    for (size_t i = 0; i < pts3D.size(); ++i) {
        pts3D_H.at<double>(0, i) = pts3D[i].x;
        pts3D_H.at<double>(1, i) = pts3D[i].y;
        pts3D_H.at<double>(2, i) = pts3D[i].z;
        pts3D_H.at<double>(3, i) = 1.0f; 
    }

    // Step 2: multiply Pose matrix by homogeneous coordinates to get homogeneous 2D points
    pts2D_H = pose * pts3D_H;

    // Step 3: normalise x and y cordinates with z
    int limit_1 = 0, limit_2 = 0, limit_3 = 0;          // For debugging purposes to count number of values within ranges specified below
    for (int i = 0; i < pts2D_H.cols; i++) {
        // Extract column
        cv::Mat column = pts2D_H.col(i);
        
        // Normalise based on z
        double z = column.at<double>(2);
        double x = column.at<double>(0) / z;
        double y = column.at<double>(1) / z;

        pts2D_H_N.push_back(cv::Point2f(x, y));
    }

    return pts2D_H_N;
}

/*========================================================================================================================================
        The function returns the reprojection error using the Pose Matrix, 3D world points from Tiangulation and 2D points
                                from the epipolar class that returns the inliers.
==========================================================================================================================================*/

double reprojection_error(const std::vector<cv::Point2f>& pts2DActual, const std::vector<cv::Point2f>& pts2DPose, 
                    const bool& average, const bool& view, const std::string& title){
    // Containers used in function
    double tempError, relativeError = 0.0;              // To store the temporary error and error
    int limit_1 = 0, limit_2 = 0, limit_3 = 0;

    // Euclidean distance
    for (int i = 0; i < pts2DActual.size(); i++) {

        // Extract points 
        double xError = (pts2DActual[i].x - pts2DPose[i].x);
        double yError = (pts2DActual[i].y - pts2DPose[i].y);

        // Assign to temp value
        tempError = std::pow((std::pow(xError, 2) + std::pow(yError, 2)), 0.5);

        // Add temp value to finale error
        relativeError += tempError;

        /*
        The below section is for counting the number of matches that are within
        the limits specified
        */

        // Count limit_1 if values within 0 < x < 1
        if (tempError >= 0 && tempError < 1){
            limit_1++;
        }
        // Count limit_2 if values within 1 < x < 5
        else if (tempError > 1 && tempError < 6){
            limit_2++;
        }
        // Count limit_3 if values >  6
        else if(tempError > 6){
            limit_3++;
        }
        else{
            std::cout << "Error counting matches" << std::endl;
        }
    }
    // Display values in limits
    if (view){
        std::cout << "\n\n"<< title << "\nNumber of Matches.\n"
                "0 <= x < 1 -> " << limit_1 <<
                "\n1 < x < 6  -> " << limit_2 <<
                "\nx > 6      -> " << limit_3 <<"\n";
    }
    // Step 5: Return error as sum or average

    if (!average){
        return relativeError;
    }
    else{
        return relativeError / pts2DActual.size();
    }
}


/*========================================================================================================================================
                        The function projects 2D points on image to visulaise reprojection error
==========================================================================================================================================*/

void visualise_reprojection(const cv::Size& imageSize, const int& imageNum, const std::vector<cv::Point2f> pts2DActual, const std::vector<cv::Point2f> pts2DPose){

    // Create window
    std::string windowName = "2D Points (image " + std::to_string(imageNum) + " )";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    // Create blank image for 2D points
    cv::Mat image = cv::Mat::zeros(imageSize.height, imageSize.width, CV_8UC3);

    // Draw the Actual 2D points as green circles
    for (const cv::Point2f& points : pts2DActual) {
        cv::circle(image, points, 5, cv::Scalar(0, 255, 0), -1); 
    }

    // Draw the Pose 2D points as green circles
    for (const cv::Point2f& points : pts2DPose) {
        cv::circle(image, points, 5, cv::Scalar(0, 0, 255), -1); 
    }

    // Display the canvas in the window
    cv::imshow(windowName, image);

    // Wait for key 
    cv::waitKey(0);
}

/*========================================================================================================================================
        The function returns the reprojection error visualised using the Pose Matrix, 3D world points from Tiangulation and 2D points
                                from the epipolar class that returns the inliers.
==========================================================================================================================================*/

void visualise_reprojection_error(const std::vector<std::string>& textImages, const int& imageIterations, const cv::Mat& kMatrix, const cv::Size& imageSize){

    // Containers
    int i = -1;                                         // iteraration beginning
    int j;                                              // used for title string in reprojection error
    cv::Mat r1Matrix = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat t1Matrix = cv::Mat::zeros(3, 1, CV_64F);
    cv::Mat currPose;
    cv::Mat nextPose;
    cv::Mat iterRot;
    cv::Mat iterTra;
    std::vector<cv::Point2f> estimate2Dpoints;

    // loop through images
    while (i < imageIterations){
        // Set previous and next images
        //std::cout << "\n\nCurrent image: " << textImages[++i] << "\n";
        //std::cout << "\nNext image: " << textImages[++i] << "\n";

        //=============== Image conversion ======================//
        // Class construct parameters: ImageConversion(imageFile)
        ImageConversion currentImage_grey(textImages[++i]);       
        ImageConversion nextImage_grey(textImages[++i]);

        // Convert Image
        currentImage_grey.convert2gray();
        nextImage_grey.convert2gray();

        //=============== Feature detection ======================//
        // Class construct parameters: FeatureDetect(imageGrey)
        FeatureDetect current_features(currentImage_grey.getGreyImage());
        FeatureDetect next_features(nextImage_grey.getGreyImage());

        // Select feature detect method
        current_features.feature_detect("FAST");
        next_features.feature_detect("FAST");

        //=============== Feature Matching ======================//
        FeatureMatching image_matches(current_features.getDescriptors(), next_features.getDescriptors(),
                                  current_features.getKey(), next_features.getKey());

        // Perform feature matching
        image_matches.match_features(2, 0.8);

        //=============== Epipolar Geometry ======================//
        EpipolarGeometry epipolarObject(image_matches.getMatches(), image_matches.get2Dpoints_1(), image_matches.get2Dpoints_2(),
                                    current_features.getKey(), next_features.getKey(), currentImage_grey.getGreyImage(),
                                    nextImage_grey.getGreyImage(), kMatrix);

        // Perform epipolar geometry
        epipolarObject.perform_epipolar_geometry(1, 0.99);

        //=============== Triangulation ========================//

        currPose = poseMatrix(kMatrix, r1Matrix, t1Matrix, true);
        nextPose = poseMatrix(kMatrix, epipolarObject.getRotation(), epipolarObject.getTranslation(), true);

        // Class construct parameters: Triangulation(poseMatrix1, poseMatrix2, inlier1, inlier2)
        Triangulation triangulateObject(currPose, nextPose, epipolarObject.getInliers_1(), epipolarObject.getInliers_2());

        // Create 3D points
        triangulateObject.perform_triangulation();

        //=============== Reprojection Error ========================//
        j = i - 1;                      // selects title name from images vector
        std::string currentImage = textImages[j];
        std::string nextImage = textImages[++j];


        // Current Image reprojection error
        estimate2Dpoints = create_2D_points_from_3D(currPose, triangulateObject.get3Dpoints());
        reprojection_error(epipolarObject.getInliers_1(), estimate2Dpoints, true, true, currentImage);
        visualise_reprojection(imageSize, j, epipolarObject.getInliers_1(), estimate2Dpoints);
        


        // Next Image reprojection error
        estimate2Dpoints = create_2D_points_from_3D(nextPose, triangulateObject.get3Dpoints());
        reprojection_error(epipolarObject.getInliers_2(), estimate2Dpoints, true, true, nextImage);
        visualise_reprojection(imageSize, j + 1, epipolarObject.getInliers_2(), estimate2Dpoints);
                           
    }


}