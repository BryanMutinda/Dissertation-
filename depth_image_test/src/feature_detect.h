#ifndef FEATURE_DETECT_H
#define FEATURE_DETECT_H

#include "functions_and_libs.h"

class FeatureDetect {
private:
    // Containers 
    std::vector<cv::Point2f> points2D;          // feature detection method
    std::vector<cv::KeyPoint> keypoints;        // keypoints
    cv::Mat imageGrey;                          // Grey image form coloured conversion
    cv::Mat descriptors;                        // descriptors
    cv::Mat imageKeypoints;                     // image with keypoints superimposed
    size_t keyPointsBefore, keyPointsAfter;     // Keypoint sizes before and after preprocessing 

    // Feature detectors
    void feature_detection_ORB();
    void feature_detection_FAST();
    void feature_detection_SIFT();
    void feature_detection_SURF();
    void feature_detection_BRISK();

    // /Pre-process Keypoints
    void remove_duplicated_KeyPoints();         // Filter duplicated Keypoints
    
    // Create 2d points
    void create_2D_points();                   

public:
    // Constructor
    FeatureDetect(const cv::Mat& imageGrey);
    
    // Select feature detection
    void feature_detect(const std::string& method);
   
    // Get information
    std::vector<cv::KeyPoint> getKey(); 
    cv::Mat getDescriptors();
    void displayKeySize();
    cv::Mat getImageGrey();

    // Display images
    void displayGreyPoints(const int& width, const int& height);
};

#endif // FEATURE_DETECT_H
