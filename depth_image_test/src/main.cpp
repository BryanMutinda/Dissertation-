#include "functions_and_libs.h"

/* ======================================================================================================= 
                                    Global space containers 
==========================================================================================================*/

// Camera Intrinsic Parameters
cv::Mat kMatrix = (cv::Mat_<double>(3, 3) << 3310.40, 0.00, 316.73, 
                                    0.00, 3325.50, 200.55, 
                                    0.00, 0.00, 1.00);

// First rotation and translation
cv::Mat r1Matrix = cv::Mat::eye(3, 3, CV_64F);
cv::Mat t1Matrix = cv::Mat::zeros(3, 1, CV_64F);

// Image files
std::string image1 = "../images/dinoSparseRing/dinoSR0001.png",
            image2 = "../images/dinoSparseRing/dinoSR0002.png",
            image3 = "../images/dinoSparseRing/dinoSR0003.png";



int main() {

/* ======================================================================================================= 
                                    Image Conversion (Images 1 & 2)
==========================================================================================================*/

    // Class construct parameters: ImageConversion(imageFile)
    ImageConversion image1_grey(image1);       
    ImageConversion image2_grey(image2);

    // Convert Image
    image1_grey.convert2gray();
    image2_grey.convert2gray();


/* ======================================================================================================= 
                                    Feature Detection (Images 1 & 2)
==========================================================================================================*/  

    // Class construct parameters: FeatureDetect(imageGrey)
    FeatureDetect image1_features(image1_grey.getGreyImage());
    FeatureDetect image2_features(image2_grey.getGreyImage());

    // Select feature detect method
    image1_features.feature_detect("FAST");
    image2_features.feature_detect("FAST");
  

/* ======================================================================================================= 
                                    Feature Matching (Images 1 & 2)
==========================================================================================================*/

    // Class construct parameters: FeatureMatching(image_1_descriptors, image_2_descriptors, 
    //                                             image_1_keypoints, image_2_keypoints)
    FeatureMatching image_matches_1_2(image1_features.getDescriptors(), image2_features.getDescriptors(),
                                  image1_features.getKey(), image2_features.getKey());

    // Perform feature matching
    image_matches_1_2.match_features(2, 0.8);


/* ======================================================================================================= 
                                    Epipolar Geometry (Images 1 & 2)
==========================================================================================================*/

    // Class construct parameters: EpipolarGeometry(matches, image_1_2D_points, image_2_2D_points, keypoints1
    //                                             keypoints2, image1, image2, kMatrix)
    EpipolarGeometry epipolarObject(image_matches_1_2.getMatches(), image_matches_1_2.get2Dpoints_1(), image_matches_1_2.get2Dpoints_2(),
                                    image1_features.getKey(), image2_features.getKey(), image1_grey.getGreyImage(),
                                    image2_grey.getGreyImage(), kMatrix);

    // Perform epipolar geometry
    epipolarObject.perform_epipolar_geometry(1, 0.99);


/* ======================================================================================================= 
                                    Triangulation (Images 1 & 2)
==========================================================================================================*/

    // Function returns poseMatrix
    cv::Mat poseMatrix_1 = poseMatrix(kMatrix, r1Matrix, t1Matrix, true);
    cv::Mat poseMatrix_2 = poseMatrix(kMatrix, epipolarObject.getRotation(), epipolarObject.getTranslation(), true);

    // Class construct parameters: Triangulation(poseMatrix1, poseMatrix2, inlier1, inlier2)
    Triangulation triangulateObject(poseMatrix_1, poseMatrix_2, epipolarObject.getInliers_1(), epipolarObject.getInliers_2());

    // Create 3D points
    triangulateObject.perform_triangulation();


/* ======================================================================================================= 
                                Feature Matching (Images 2 & 3)
==========================================================================================================*/
    //======= Image conversion =========//
    ImageConversion image3_grey(image3);
    image3_grey.convert2gray();       

    //======= Feature detection =========//
    FeatureDetect image3_features(image3_grey.getGreyImage());
    image3_features.feature_detect("FAST");

    //======= Feature Matching =========//
    FeatureMatching image_matches_2_3(image2_features.getDescriptors(), image3_features.getDescriptors(),
                                  image2_features.getKey(), image3_features.getKey());

    image_matches_2_3.match_features(2, 0.8);       // Perform feature matching


/* ======================================================================================================= 
                                Resection (Images 1, 2 & 3)
==========================================================================================================*/

    // Assuming no distortion
    cv::Mat cameraDistortion = cv::Mat::zeros(5, 1, CV_64F);

    Resection resectionObject(image_matches_1_2.getMatches(), image_matches_2_3.getMatches(),
                     triangulateObject.get3Dpoints(), image3_features.getKey());

    resectionObject.match_matches();
    resectionObject.performResection(kMatrix, cameraDistortion);

    std::cout << resectionObject.getRotation() << "\n\n" << rMatrix_2_angle(resectionObject.getRotation());

    // Containers for bundle adjustment
    cv::Mat rVector = resectionObject.getRotationVector();
    cv::Mat tVector = resectionObject.getTranslation();
    std::vector<cv::Point2f> points2D = resectionObject.get2Dpoints();
    std::vector<cv::Point3f> points3D = resectionObject.get3Dpoints();


/* ======================================================================================================= 
                                Bundle adjusment (Images 1, 2 & 3)
==========================================================================================================*/
    
    // Variables
    cv::Size imageSize = image1_grey.getGreyImage().size();             // Image size


/*
    // Variables
    std::vector<cv::Mat> rBundle, tBundle;
    std::vector<cv::Point3f> bundle3Dpoints;


    // Initialize bundle adjustment
    cv::sfm::simple_pipeline pipeline; // Example, if available
    pipeline.initialize(bundle3Dpoints, projections_float, imagePoints);

    */

/*
    cv::Mat rVectorBundle, tVectorBundle;
    cv::sfm::SFMLibmvEuclideanReconstruction::run(resectionObject.get2Dpoints(), kMatrix, rVectorBundle, tVectorBundle,bundle3Dpoints)

*/

/*
    cv::detail::BundleAdjusterBase::estimate	(	const std::vector< ImageFeatures > & 	features,
const std::vector< MatchesInfo > & 	pairwise_matches,
std::vector< CameraParams > & 	cameras 
)	
*/

   


/*
    // Perform bundle adjustment
    cv::sfm::bundleAdjust(points3D, points2D, kMatrix, rVector, tVector, cameraDistortion);
    

    // Output optimized camera parameters
    std::cout << "Optimized camera matrix: " << std::endl << kMatrix << std::endl;

    for (size_t i = 0; i < rVector.size(); ++i) {
        std::cout << "Optimized rotation vector " << i << ": " << std::endl << rVector[i] << std::endl;
        std::cout << "Optimized translation vector " << i << ": " << std::endl << tVector[i] << std::endl;
    }

    */

/* ======================================================================================================= 
                                Reprojection Error
==========================================================================================================*/
    // Function creates a vector of string type containing image locations
    std::vector<std::string> imageFiles = image_string_vector("../images/dinoSparseRing/dinoSR000", ".png", 1, 16);

    // Visualise's the reprojection error
    visualise_reprojection_error(imageFiles, 14, kMatrix, imageSize);

return 0;
}