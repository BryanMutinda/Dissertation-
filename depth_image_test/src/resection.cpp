#include "functions_and_libs.h"

// Constructor
Resection::Resection(const cv::Mat& kMatrix, const cv::Mat& distortion)
                    : kMatrix(kMatrix), distortion(distortion) {}

// Perform resection
void Resection::performResection(const std::vector<std::string>& images){
    // Loop through images
    for(int i = 0; i < images.size() - 1; i++){
        // Debugging image input
        //std::cout << "\n1 ->" << images[i] << "\n2 ->" << images[i + 1] << "\n";

        //  ============= Image Conversion ================================//
        // Class construct parameters: ImageConversion(imageFile)
        ImageConversion imageCurrent(images[i]);       
        ImageConversion imageNext(images[i + 1]);

        // Convert Image
        imageCurrent.convert2gray();
        imageNext.convert2gray();

        //  ============= Feature Detecetion ==============================//
        // Class construct parameters: FeatureDetect(imageGrey)
        FeatureDetect imageCurrent_features(imageCurrent.getGreyImage());
        FeatureDetect imageNext_features(imageNext.getGreyImage());

        // Select feature detect method
        imageCurrent_features.feature_detect("FAST");
        imageNext_features.feature_detect("FAST");

        //  ============= Feature Matching ================================//
        /* Class construct parameters: FeatureMatching(image_1_descriptors, 
                image_2_descriptors, image_1_keypoints, image_2_keypoints)*/
        FeatureMatching image_matches(imageCurrent_features.getDescriptors(), 
                                imageNext_features.getDescriptors(),
                                imageCurrent_features.getKey(), 
                                imageNext_features.getKey());

        // Perform feature matching
        image_matches.match_features(2, 0.8);

        //  ============= Epipolar Geometry ================================//
        /* Class construct parameters: EpipolarGeometry(matches, image_1_2D_points,
         image_2_2D_points, keypoints1, keypoints2, image1, image2, kMatrix)*/
        EpipolarGeometry epipolarObject(image_matches.getMatches(), 
            image_matches.get2Dpoints_1(), image_matches.get2Dpoints_2(),
            imageCurrent_features.getKey(), imageNext_features.getKey(), 
            imageCurrent.getGreyImage(), imageNext.getGreyImage(), kMatrix);

        // Perform epipolar geometry
        epipolarObject.perform_epipolar_geometry(1, 0.99);

        //  ============= Triangulation ====================================//
        // Switch rotation and translation matrices depending on scenario to create pose matrix
        if( i == 0){
            cv::Mat r1Matrix = cv::Mat::eye(3, 3, CV_64F), t1Matrix = cv::Mat::zeros(3, 1, CV_64F);
            poseCurrent = poseMatrix(kMatrix, r1Matrix, t1Matrix, true);
            poseNext = poseMatrix(kMatrix, epipolarObject.getRotation(), epipolarObject.getTranslation(), true);

            // Assign current rotation and translation matrices for next loop
            previousRotationMatrix = epipolarObject.getRotation();
            previousTranslationVector = epipolarObject.getTranslation();
        }
        else{
            poseCurrent = poseMatrix(kMatrix, previousRotationMatrix, previousTranslationVector, true);
            poseNext = poseMatrix(kMatrix, epipolarObject.getRotation(), epipolarObject.getTranslation(), true);

            // Assign current rotation and translation matrices for next loop
            previousRotationMatrix = epipolarObject.getRotation();
            previousTranslationVector = epipolarObject.getTranslation();
        }

        // Class construct parameters: Triangulation(poseMatrix1, poseMatrix2, inlier1, inlier2)
        Triangulation triangulateObject(poseCurrent, poseNext, epipolarObject.getInliers_1(), epipolarObject.getInliers_2());

        // Create 3D points
        triangulateObject.perform_triangulation();

        // Peform solvePnP for each 2D points
        for(int j = 0; j < 2; j++){
            if (j == 0){
                // Create rotation and translation vectors using PnP Pg 647 - 648
                cv::solvePnP(triangulateObject.get3Dpoints(), epipolarObject.getInliers_1(), kMatrix, distortion, rVector, tVector);

                // Using Rodrigues to converts rotation vector to rotation matrix
                cv::Rodrigues(rVector, rotationMatrix);

                // Convert rVector to angle in degrees
                angle = cv::norm(rVector) * (180.0 / CV_PI);

                // Push rotation and translation matrices nad angles
                rotationMatrixVector.push_back(rotationMatrix);
                translationVectorVector.push_back(tVector);
                angles.push_back(angle);
            }
            else{
                // Create rotation and translation vectors using PnP Pg 647 - 648
                cv::solvePnP(triangulateObject.get3Dpoints(), epipolarObject.getInliers_2(), kMatrix, distortion, rVector, tVector);

                // Using Rodrigues to converts rotation vector to rotation matrix
                cv::Rodrigues(rVector, rotationMatrix);

                // Convert rVector to angle in degrees
                angle = cv::norm(rVector) * (180.0 / CV_PI);

                // Push rotation and translation matrices nad angles
                rotationMatrixVector.push_back(rotationMatrix);
                translationVectorVector.push_back(tVector);
                angles.push_back(angle);
            }
        }   
    }
}  

// return rotation matrix
std::vector<cv::Mat> Resection::getRotation(){
    return rotationMatrixVector;
}

// return translation
std::vector<cv::Mat> Resection::getTranslation(){
    return translationVectorVector;
}

// return angle in degrees
std::vector<double> Resection::getRotationAngle(){
    return angles;
}