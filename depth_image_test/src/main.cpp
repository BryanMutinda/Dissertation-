#include "functions_and_libs.h"

/* ======================================================================================================= 
                                    Global space containers 
==========================================================================================================*/
cv::Mat kMatrix, 
        r1Matrix, 
        t1Matrix, 
        rInverse, 
        r1Corrected, 
        r2Corrected,
        t2Corrected, 
        cameraDistortion;

double errorSum, errorAvg;


int main() {
    // Image files
    std::string image1 = "../images/dinoSparseRing/dinoSR0001.png";
    std::string image2 = "../images/dinoSparseRing/dinoSR0002.png";

    // Camera Intrinsic Parameters
    kMatrix = (cv::Mat_<double>(3, 3) << 3310.40, 0.00, 316.73, 
                                         0.00, 3325.50, 200.55, 
                                         0.00, 0.00, 1.00);


/* ======================================================================================================= 
                                    Image Conversion 
==========================================================================================================*/

/*
Image class takes a string with filename and returns a grey image

USAGE: method name -> description of method
getGreyImage() -> returns grey image
*/

    // Class construct parameters: ImageConversion(imageFile)
    ImageConversion image1_grey(image1);       
    ImageConversion image2_grey(image2);

    // Convert Image
    image1_grey.convert2gray();
    image2_grey.convert2gray();


/* ======================================================================================================= 
                                    Feature Detection
==========================================================================================================*/

/*
Feature detection class uses FAST, SIFT, SURF, BRISK, ORB to output keypoints and descriptors. 

USAGE: method name -> description of method
feature_detect(detectionType) -> uses the detection type to create keypoints & descriptors
getKey() -> returns keyponts
getDescriptors() -> returns descriptors
displayKeySize() -> returns the keypoint sizes before and after removing duplicate keypoints
displayGreyPoints(int width, int height) -> returns image displaying keypoints with specified  window size
                                         -> e.g. displayKeySize(1200, 800)
*/  

    // Class construct parameters: FeatureDetect(imageGrey)
    FeatureDetect image1_features(image1_grey.getGreyImage());
    FeatureDetect image2_features(image2_grey.getGreyImage());

    // Select feature detect method
    image1_features.feature_detect("FAST");
    image2_features.feature_detect("FAST");
  

/* ======================================================================================================= 
                                    Feature Matching
==========================================================================================================*/

/*
Feature matching class uses descriptors from the 1st & 2nd image to perform feature matching

USAGE: method name -> description of method
match_features(k, ratio) -> performs feature matching where k is the number of neighbours
                         -> and ratio is th lowe's ratio value
getMatches() -> returns the matches
get2Dpoints_1() -> returns 2D points of image 1
get2Dpoints_2() -> returns 2D points of image 2
*/

    // Class construct parameters: FeatureMatching(image_1_descriptors, image_2_descriptors, 
    //                                             image_1_keypoints, image_2_keypoints)
    FeatureMatching image_matches(image1_features.getDescriptors(), image2_features.getDescriptors(),
                                  image1_features.getKey(), image2_features.getKey());

    // Perform feature matching
    image_matches.match_features(2, 0.8);


/* ======================================================================================================= 
                                    Epipolar Geometry
==========================================================================================================*/
/*

/* 
Epipolar geometry class uses the image matches, 2D points, keypoints and kMatrix to recover the rotation
& translation matrix and vector respectively.

USAGE: method name -> description of method
perform_epipolar_geometry((maxPixelDist, confidence) -> recovers the rotation and translation where 
                                                     -> maxPixelDist = range between pixels (ranges between 1 - 3) Pg 720
                                                     -> confidence = number of iterations (ranges between 0 -1) Pg 720
getRotation() -> returns rotation
getTranslation() -> returns translation
getInliers_1() -> returns 2D inliers for image 1
getInliers_2() -> returns 2D inliers for image 2
displayRotation() -> displays rotation
displayTranslation() -> displays translation
displayRansacMatches() -> displays matches before and after RANSAC
beforeRANSAC(width, height) -> returns image with matches before RANSAC where window size is inserted as an integer
afterRANSAC(width, height) -> returns image with matches before RANSAC where window size is inserted as an integer
*/

    // Class construct parameters: EpipolarGeometry(matches, image_1_2D_points, image_2_2D_points, keypoints1
    //                                             keypoints2, image1, image2, kMatrix)
    EpipolarGeometry epipolarObject(image_matches.getMatches(), image_matches.get2Dpoints_1(), image_matches.get2Dpoints_2(),
                                    image1_features.getKey(), image2_features.getKey(), image1_grey.getGreyImage(),
                                    image2_grey.getGreyImage(), kMatrix);

    // Perform epipolar geometry
    epipolarObject.perform_epipolar_geometry(1, 0.99);

    // View matches after RANSAC
    epipolarObject.afterRANSAC(1200, 800);


/* ======================================================================================================= 
                                    Triangulation
==========================================================================================================*/

r1Matrix = cv::Mat::eye(3, 3, CV_64F);
t1Matrix = cv::Mat::zeros(3, 1, CV_64F);

// Function returns poseMatrix
cv::Mat poseMatrix_1 = poseMatrix(kMatrix, r1Matrix, t1Matrix, true);
cv::Mat poseMatrix_2 = poseMatrix(kMatrix, epipolarObject.getRotation(), epipolarObject.getTranslation(), true);

/*
Triangulation class uses 2D points from both images and returns the 3D world points

USAGE: method name -> description of method
perform_triangulation() -> performs the triangulation
get3Dpoints() -> returns 3D points
*/

    // Class construct parameters: Triangulation(poseMatrix1, poseMatrix2, inlier1, inlier2)
    Triangulation triangulateObject(poseMatrix_1, poseMatrix_2, epipolarObject.getInliers_1(), epipolarObject.getInliers_2());

    // Create 3D points
    triangulateObject.perform_triangulation();


/* ======================================================================================================= 
                                    Depth Map
==========================================================================================================*/

    // function parameters: createDepthMap(imageSize, kMatrix, 3D_Points, viewMap)
    createDepthMap(image1_grey.getGreyImage().size(), kMatrix, triangulateObject.get3Dpoints(), true);

    // Save 3D points to visualise them in MeshLab
    std::string points3D_1 = "../points3D/image_1.ply";
    save_points3d(triangulateObject.get3Dpoints(), points3D_1);


/* ======================================================================================================= 
                                    Rotation Analysis
==========================================================================================================*/
    // Import rotation & translation from dataset and code
    cv::Mat extern r1Dataset;
    cv::Mat extern r2Dataset;
    cv::Mat extern t1Dataset;
    cv::Mat extern t2Dataset;

    // Shift R2 based on inverse of R1
    cv::invert(r1Dataset, rInverse);
    r2Corrected = rInverse * r2Dataset;

    // Shift t2 based on t1
    t2Corrected = t2Dataset - t1Dataset;

    std::cout << "Rotation from dataset:\n" << rMatrix_2_angle(r2Corrected) 
              << "\nRotation from code:\n " << rMatrix_2_angle(epipolarObject.getRotation());

    std::cout << "\nRotation Matrix from dataset:\n" << r2Corrected
              << "\nRotation Matrix from code:\n" << epipolarObject.getRotation() << std::endl;

    // Superimpose image 1 -> image2 using rotation and translation from dataset
    superimpose_images(image1, image2, r2Corrected, t2Corrected, 2000, 1200, "Dataset");

    // Superimpose image 1 -> image2 using rotation and translation from code
    superimpose_images(image1, image2, epipolarObject.getRotation(), epipolarObject.getTranslation(), 2000, 1200, "Code");

    // Superimpose image 2 -> using rotation matrix from dataset and code
    superimpose_images_similar(image1, r2Corrected, epipolarObject.getRotation(), 2000, 1200, "Combined Dataset & Code");


/* ======================================================================================================= 
                                    Reprojection Error Images 1 & 2
==========================================================================================================*/

    // Function parameters: reprojection_error(Pose Matrix, Points 2D, Points 3D)
    double image1_SUM_RE = reprojection_error(poseMatrix_1, epipolarObject.getInliers_1(), triangulateObject.get3Dpoints(), false, true, "Image 1:");
    double image1_AVG_RE = reprojection_error(poseMatrix_1, epipolarObject.getInliers_1(), triangulateObject.get3Dpoints(), true, false, "Image 1:");

    double image2_SUM_RE = reprojection_error(poseMatrix_2, epipolarObject.getInliers_2(), triangulateObject.get3Dpoints(), false, true, "Image 2:");
    double image2_AVG_RE = reprojection_error(poseMatrix_2, epipolarObject.getInliers_2(), triangulateObject.get3Dpoints(), true, false, "Image 2:");

    std::cout <<"Image 1: \n"<< "Sum Relative Error: " << image1_SUM_RE << std::endl;
    std::cout << "Average Relative Error: " << image1_AVG_RE << std::endl;

    std::cout <<"Image 2: \n"<< "Sum Relative Error: " << image2_SUM_RE << std::endl;
    std::cout << "Average Relative Error: " << image2_AVG_RE << std::endl;


/* ======================================================================================================= 
                                                Resection 
==========================================================================================================*/

    // Function creates a vector of string type containing image locations
    std::vector<std::string> imageFiles = image_string_vector("../images/dinoSparseRing/dinoSR000", ".png", 1, 16);

    // Assuming no distortion
    cameraDistortion = cv::Mat::zeros(5, 1, CV_64F);

/*
Resction class uses kMatrix, distortion and vector containing the images
to return a vector with the rotation, translation and angles in Degrees

USAGE: method name -> description of method
performResection(imagesVector) -> performs the resection and creates necessary matrices
getRotation() -> returns vector with rotations
getTranslation() -> returns vector with translations
getRotationAngle() -> returns vector with angles
*/

    // Class Constructor parameters: Resection(kMatrix, distortion)
    Resection resectionObject(kMatrix, cameraDistortion);

    // Perform resction
    resectionObject.performResection(imageFiles);

    // View angles
    std::vector<double> angles = resectionObject.getRotationAngle();
    for (auto angle :angles){
        std::cout << angle << "\n";
    }

    std:: cout << angles.size();
return 0;
}