#include "functions_and_libs.h"

// Constructor
FeatureDetect::FeatureDetect(const cv::Mat& imageGrey) : imageGrey(imageGrey) {}

void FeatureDetect::feature_detection_ORB(){
    // ORB object
    int numberFeatures = 700;   // Number of features
    cv::Ptr<cv::ORB> orb = cv::ORB::create(numberFeatures);

	// Detect keypoints and compute descriptors
    orb->detectAndCompute(imageGrey, cv::noArray(), keypoints, descriptors);
}

void FeatureDetect::feature_detection_FAST(){
    /*Threshold parameter decides whether a point within the cirle around a
    pixel should be considered a key point or not. 
            
    The higher the threshold the fewer the keypoints detected as definition
    of keypoint becomes stricter i.e. pixels are darker or lighter 
    Pg 541 - 543

    nonMaxSupress boolean turns on or off the suppression of neighbouring points
    with inferior scores. Thus removes redundant keypoints as determines the
    circumference of the circle of sampled points Pg 543

    ORB extractor is used as FAST is not a complete algorithm that can use 
    cv::Feature2D::detectAndCompute() Pg 521
    */
            
    // Fast object
    int threshold = 0;             // Threshold for the FAST algorithm based on Pg 543 is 10
    bool nonMaxSuppression = true;  // Non-maximum suppression
    cv::Ptr<cv::FastFeatureDetector> detector = cv::FastFeatureDetector::create(threshold, nonMaxSuppression);
		
	// Create Keypoints
    detector->detect(imageGrey, keypoints);
    
    // Compute descriptors
    cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
    extractor->compute(imageGrey, keypoints, descriptors);
}

void FeatureDetect::feature_detection_SIFT(){
    /* Number of features input determines the number of features to use Pg 547

    Other inputs that may be considered are: (Pg 547)
    int nOctaveLayers = 3;                  // :Layers in each octave
    double contrastTHreshold = 0.04;        // filters out weak features
    double edgeThreshold = 10;              // filter out "edge" features
    double sigma = 1.6;                     // Variance of level-0 Gaussian
    */

    // SIFT object
    int numberFeatures = 200;           // Number of features
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create(numberFeatures);

    // Detect keypoints and compute descriptors
    sift->detectAndCompute(imageGrey, cv::noArray(), keypoints, descriptors);
}

void FeatureDetect::feature_detection_SURF(){
    /* Uses Hessian threshold which keeps features above a threshold Pg 553

    Other inputs that may be considered are: 
    int nOctaves = 4;                       // Number of pyramid octaves
    int nOctaveLayers = 3;                  // Number of images in each layers in each octave
    double contrastTHreshold = 0.04;        // filters out weak features
    double edgeThreshold = 10;              // filter out "edge" features
    double sigma = 1.6;                     // Variance of level-0 Gaussian
    */

    // SURF object
    // Hessian Threshold i.e. number of features
    int numberFeatures = 1;           // Number of features
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(numberFeatures);

    // Detect keypoints and compute descriptors
    surf->detectAndCompute(imageGrey, cv::noArray(), keypoints, descriptors);
}

void FeatureDetect::feature_detection_BRISK(){
    /*Threshold parameter is based on the FAST feature detection with the
    improvement of attempting to identify a scale for feature as well as 
    image orientation Pg 561 . 
            
    The higher the threshold the fewer the keypoints detected as definition
    of keypoint becomes stricter i.e. pixels are darker or lighter 
    Pg 541 

    Other inputs: (Pg 564)
    int octaves = 3;                // N doublings in pyramid
    float patternScale = 1.0f       // Rescale default pattern
    */

    // BRISK object
    int threshold = 7;                  // Threshold for BRISK
    cv::Ptr<cv::BRISK> brisk = cv::BRISK::create(threshold);

    // Detect keypoints and compute descriptors
    brisk->detectAndCompute(imageGrey, cv::noArray(), keypoints, descriptors);
}

// Pre-process Keypoints
void FeatureDetect::remove_duplicated_KeyPoints(){
    keyPointsBefore = keypoints.size();                  // Before duplicates removed
    cv::KeyPointsFilter::removeDuplicated(keypoints);
    keyPointsAfter = keypoints.size();                   // After duplicates removed
};
      
// Function to select feature detection method
void FeatureDetect::feature_detect(const std::string& method){
    // FAST feature detection
    if (method == "FAST"){
        feature_detection_FAST();
        remove_duplicated_KeyPoints();
    }
    // SIFT feature detection
    else if (method == "SIFT"){
        feature_detection_SIFT();
        remove_duplicated_KeyPoints();
    }
    // SURF feature detection
    else if (method == "SURF"){
        feature_detection_SURF();
        remove_duplicated_KeyPoints();
    }
    // BRISK feature detection
    else if (method == "BRISK"){
        feature_detection_BRISK();
        remove_duplicated_KeyPoints();
    }
    // ORB feature detection
    else if (method == "ORB"){
        feature_detection_ORB();
        remove_duplicated_KeyPoints();
    }
    else{
        std::cout << "\nInsert a correct method\n";
    }

}

std::vector<cv::KeyPoint> FeatureDetect::getKey() {
    return keypoints;
}

cv::Mat FeatureDetect::getDescriptors() {
    return descriptors;
}

void FeatureDetect::displayKeySize(){
    // Display points set against points found
    std::cout << "Detected before preprocessing-> " << keyPointsBefore << " keypoints." << std::endl;
    std::cout << "Detected after preprocessing-> " << keyPointsAfter << " keypoints." << std::endl;
}

void FeatureDetect::displayGreyPoints(const int& width, const int& height) {
    cv::drawKeypoints(imageGrey, keypoints, imageKeypoints, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::namedWindow("KeyPoints", cv::WINDOW_NORMAL);
    cv::resizeWindow("KeyPoints", width, height); 
    cv::imshow("KeyPoints", imageKeypoints); // Display KeyPoints
    cv::waitKey(0); // Wait for a key press
    cv::destroyWindow("KeyPoints"); // Destroy the window
}