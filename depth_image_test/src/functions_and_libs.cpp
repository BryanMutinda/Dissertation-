#include "functions_and_libs.h"


/* ==================================================================================================================== 
                                The function returns the Pose Matrix
======================================================================================================================= */

cv::Mat poseMatrix(const cv::Mat& K, const cv::Mat& R, const cv::Mat& t, bool returnPose){
    cv::Mat pose = cv::Mat::eye(3, 4, CV_64F);
    // Add rotation matrix to pose matrix
    R.copyTo(pose(cv::Rect(0, 0, 3, 3)));
    // Add the translation vector t to the pose matrix
    t.copyTo(pose.col(3));

    // if true returns P = K * pose
    if (returnPose){
        return K * pose;
    }
    // if not true returns the pose alone
    else{
        return pose;
    }
}

/* ==================================================================================================================== 
                                The function visualise the depth map in a 2D plane 
======================================================================================================================= */

void createDepthMap(const cv::Size& imageSize, const cv::Mat& k, const std::vector<cv::Point3f>& pts3D, const bool& view){    
    // Create a blank depth map (initialized to zeros)
    cv::Mat depthMap(imageSize, CV_64F, cv::Scalar(0));

    // Project 3D points to 2D image plane
    for (const auto& point : pts3D) {
        // Convert 3D point to homogeneous coordinates
        cv::Mat point3D_h = (cv::Mat_<double>(4, 1) << point.x, point.y, point.z, 1.0);

        // Project the 3D point to 2D
        cv::Mat point2D_h = k * point3D_h(cv::Range(0, 3), cv::Range::all());

        // Normalize the projected point
        cv::Point2f point2D(point2D_h.at<double>(0) / point2D_h.at<double>(2),
                            point2D_h.at<double>(1) / point2D_h.at<double>(2));

        // Set the depth value in the depth map
        int x = static_cast<int>(point2D.x);
        int y = static_cast<int>(point2D.y);

        // Ensure the point is within the image bounds
        if (x >= 0 && x < depthMap.cols && y >= 0 && y < depthMap.rows) {
            depthMap.at<double>(y, x) = point.z;
        }
    }

    if (view){
        // Normalize the depth map for visualization (optional)
        cv::normalize(depthMap, depthMap, 0, 255, cv::NORM_MINMAX, CV_8U);

        // Display the depth map
        cv::namedWindow("Depth Map", cv::WINDOW_NORMAL);
        cv::resizeWindow("Depth Map", 1200, 800); // Resize the window to 1200x800 pixels
        cv::imshow("Depth Map", depthMap);
        cv::waitKey(0);
        cv::destroyAllWindows();

    }
}

/* ============================================================================================================ 
The function saves 3D points from triangulation to a .ply file to be visualised using 3D software being MeshLab
=============================================================================================================== */

void save_points3d(const std::vector<cv::Point3f>& pts3D, const std::string& filename){
    std::ofstream file;
    file.open(filename);

    file << "ply\n";
    file << "format ascii 1.0\n";
    file << "element vertex " << pts3D.size() << "\n";
    file << "property float x\n";
    file << "property float y\n";
    file << "property float z\n";
    file << "end_header\n";

    for (const auto& pt : pts3D) {
        file << pt.x << " " << pt.y << " " << pt.z << "\n";
    }

    std::cout << "\nSaved" << filename << "\n";

    file.close();
}

/*=============================================================================================================
                        Converts Matrix to Angle in Degrees using Rodgrigues (Pg 647 - 648)
===============================================================================================================*/

double rMatrix_2_angle(const cv::Mat& rMatrix) {
    // Using Rodrigues to convert Matrix to Vector
    cv::Vec3d vector;
    cv::Rodrigues(rMatrix, vector);

    // Convert vector to angle in Degrees
    double angle = cv::norm(vector) * (180.0 / CV_PI);
    return angle;
}

/*=============================================================================================================
                                            Superimpose Images
===============================================================================================================*/
cv::Mat createHomography(const cv::Mat& rotationMatrix, const cv::Mat& translationVector) {
    // Create the 3x3 homography matrix
    cv::Mat homography = cv::Mat::eye(3, 3, CV_64F); // Initialize to identity matrix

    // Set the rotation part
    rotationMatrix(cv::Range(0, 2), cv::Range(0, 2)).copyTo(homography(cv::Range(0, 2), cv::Range(0, 2)));

    // Set the translation part
    homography.at<float>(0, 2) = translationVector.at<float>(0, 0);
    homography.at<float>(1, 2) = translationVector.at<float>(1, 0);

    return homography;
}

cv::Mat createHomographyRodrigues(const cv::Mat& rMatrix, const int& tx, const int& ty) {
    // Using Rodrigues to convert Matrix to Vector
    cv::Vec3d vector;
    cv::Rodrigues(rMatrix, vector);

    // Convert vector to angle
    double angle = cv::norm(vector);

    // Create a 3x3 homography matrices
    cv::Mat homography = cv::Mat::eye(3, 3, CV_64F);

    // Rotation Z-axis
    homography.at<double>(0, 0) = std::cos(angle);   
    homography.at<double>(0, 1) = -std::sin(angle);  
    homography.at<double>(0, 2) = tx;               
    homography.at<double>(1, 0) = std::sin(angle);   
    homography.at<double>(1, 1) = std::cos(angle);   
    homography.at<double>(1, 2) = ty;               

    return homography;
}

// Convert an image to a red-tinted image
cv::Mat makeImageRed(const cv::Mat& image) {
    cv::Mat redImage;
    std::vector<cv::Mat> channels(3);
    cv::split(image, channels);
    channels[0] = cv::Mat::zeros(image.rows, image.cols, CV_8UC1); // Blue channel to zero
    channels[1] = cv::Mat::zeros(image.rows, image.cols, CV_8UC1); // Green channel to zero
    // The Red channel remains unchanged
    cv::merge(channels, redImage);
    return redImage;
}

// Convert an image to a yellow-tinted image
cv::Mat makeImageBlue(const cv::Mat& image) {
    cv::Mat blueImage;
    std::vector<cv::Mat> channels(3);
    cv::split(image, channels);
    channels[1] = cv::Mat::zeros(image.rows, image.cols, CV_8UC1); // Green channel to zero
    channels[2] = cv::Mat::zeros(image.rows, image.cols, CV_8UC1); // Red channel to zero
    cv::merge(channels, blueImage);
    return blueImage;
}

// Concatenate images together
cv::Mat concatenateImages(const cv::Mat& img1, const cv::Mat& img2) {
    cv::Mat result;
    cv::hconcat(img1, img2, result); // Concatenate images horizontally
    return result;
}

void superimpose_images(const std::string& image1S, const std::string& image2S, const cv::Mat& rMatrix,
                        const cv::Mat& tVector, const int& width, const int& height, const std::string& title){ 
    // Load images as colour 
    cv::Mat image1 = cv::imread(image1S);
    cv::Mat image2 = cv::imread(image2S);

    // Compute homography using rotation and translation 
    cv::Mat homography = createHomography(rMatrix, tVector);

    // Warp the first image
    cv::Mat warped_image1;
    cv::warpPerspective(image1, warped_image1, homography, image2.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT);

    // Convert image colours
    cv::Mat red_image = makeImageRed(warped_image1);
    cv::Mat blue_image = makeImageBlue(image2);

    // Blend the images
    cv::Mat superImposed;
    cv::addWeighted(red_image, 0.5, blue_image, 0.5, 0, superImposed);

    // Concatenate images
    cv::Mat concatenatedImage = concatenateImages(red_image, blue_image);

    // Display images side by side
    std::string sideText = title + " (Side by side)";
    cv::namedWindow(sideText, cv::WINDOW_NORMAL);
    cv::resizeWindow(sideText, width, height);
    cv::imshow(sideText, concatenatedImage);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // Display superimposed image
    std::string imposedText = title + " (Superimposed Image)";
    cv::namedWindow(imposedText, cv::WINDOW_NORMAL);
    cv::resizeWindow(imposedText, width, height);
    cv::imshow(imposedText, superImposed);
    cv::waitKey(0);
    cv::destroyAllWindows();
 }

void superimpose_images_similar(const std::string& imageString, const cv::Mat& rMatrixData, const cv::Mat& rMatrixCode, 
                        const int& width, const int& height, const std::string& title){ 
    
    // Load images as colour 
    cv::Mat image = cv::imread(imageString);

    // Compute homography using rotation and translation 
    cv::Mat homography1 = createHomographyRodrigues(rMatrixData, 0.0, 0.0);
    cv::Mat homography2 = createHomographyRodrigues(rMatrixCode, 0.0, 0.0);

    // Warp images
    cv::Mat warped_imageData, warped_imageCode;
    cv::warpPerspective(image, warped_imageData, homography1, image.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT);
    cv::warpPerspective(image, warped_imageCode, homography2, image.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT);

    // Convert image colours
    cv::Mat red_image = makeImageRed(warped_imageData);
    cv::Mat blue_image = makeImageBlue(warped_imageCode);

    // Blend the images
    cv::Mat superImposed;
    cv::addWeighted(red_image, 0.5, blue_image, 0.5, 0, superImposed);

    // Concatenate images
    cv::Mat concatenatedImage = concatenateImages(red_image, blue_image);

    // Display images side by side
    std::string sideText = title + " (Side by side)";
    cv::namedWindow(sideText, cv::WINDOW_NORMAL);
    cv::resizeWindow(sideText, width, height);
    cv::imshow(sideText, concatenatedImage);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // Display superimposed image
    std::string imposedText = title + " (Superimposed Image)";
    cv::namedWindow(imposedText, cv::WINDOW_NORMAL);
    cv::resizeWindow(imposedText, width, height);
    cv::imshow(imposedText, superImposed);
    cv::waitKey(0);
    cv::destroyAllWindows();
 }

/*========================================================================================================================================
        The function returns the reprojection error using the Pose Matrix, 3D world points from Tiangulation and 2D points
                                from the epipolar class that returns the inliers.
==========================================================================================================================================*/

double reprojection_error(const cv::Mat& pose, const std::vector<cv::Point2f>& pts2D, const std::vector<cv::Point3f>& pts3D, 
                        const bool& average, const bool& view, const std::string& title){
    // Containers used in function
    cv::Mat pts3D_H(4, pts3D.size(), CV_64F);           // Empty 4D matrix for 3D homogeneous coordinates
    cv::Mat pts2D_H;                                    // Empty 3D matrix for 2D homogeneous coordinates
    std::vector<cv::Point3f> pts2D_H_N;                 // Normalised 3D matrix for 2D homogeneous coordinates
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

        pts2D_H_N.push_back(cv::Point3f(x, y, 1.0));
    }

    // Step 4: Euclidean distance
    for (int i = 0; i < pts2D_H_N.size(); i++) {
        // Extract points 
        double xError = (pts2D[i].x - pts2D_H_N[i].x);
        double yError = (pts2D[i].y - pts2D_H_N[i].y);

        // Assign to temp value
        tempError = std::pow((std::pow(xError, 2) + std::pow(yError, 2)), 0.5);

        // View Euclidean distance for debugging
        //std::cout << tempError << "\n";

        // Add temp value to finale error
        relativeError += tempError;

        /*
        The below section is only required for debugging and coun the number of matches that are within
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
        std::cout << title << "\nNumber of Matches.\n"
                "0 <= x < 1 -> " << limit_1 <<
                "\n1 < x < 6  -> " << limit_2 <<
                "\nx > 6      -> " << limit_3 <<"\n";
    }
    // Step 5: Return error as sum or average

    if (!average){
        return relativeError;
    }
    else{
        return relativeError / pts2D_H_N.size();
    }
}

/*=============================================================================================================
                        Function creates numbered strings in a string vector
===============================================================================================================*/
std::vector<std::string> image_string_vector(const std::string& text, const std::string& imageType, const int& start, const int& stop){
    // Containers
    std::string filename;                               // filename
    std::vector<std::string> vectorString;             // Vector output

    // Loop and create vector
    for (int i = start; i < stop + 1; i++){
        filename = text + std::to_string(i) + imageType;
        vectorString.push_back(filename);
    }

    return vectorString;
}


/*==============================================================================================================================
                    The function performs Feature Detection, Matching, Epipoloar Geometry, and Triangulation
                                            and returns the 2D points, 3D points.
================================================================================================================================*/


