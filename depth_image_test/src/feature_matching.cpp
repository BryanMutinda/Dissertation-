#include "functions_and_libs.h"

// Constructor 
FeatureMatching::FeatureMatching(const cv::Mat& descriptors1, const cv::Mat& descriptors2,
                                 const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2)
                                :descriptors1(descriptors1), descriptors2(descriptors2), 
                                 keypoints1(keypoints1), keypoints2(keypoints2) {}

// Peforms feature matching
void FeatureMatching::match_features(const int& k, const float& ratio) {
    // Match features
    cv::Ptr<cv::DescriptorMatcher> matcher;

    // Used by ORB, FAST & BRISK feature detection
    if (descriptors1.type() == CV_8U) {
        matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
    } 
        
    // Used by SIFT and SURF feature detection
    else if (descriptors1.type() == CV_32F) {
        matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    } 
    
    else {
        std::cerr << "Error: Unsupported descriptor type." << std::endl;
    }
    
    // KNN method matching. Change number of numbers to increase/decrese number
    // of neighbours
    matcher->knnMatch(descriptors1, descriptors2, knnMatches, k);

    // Lowe's ratio
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i][0].distance < ratio * knnMatches[i][1].distance) {
            goodMatches.push_back(knnMatches[i][0]);
        }
    }

    // Use good matches to get corresponding 2D points
    for (const auto& match : goodMatches) {
        points2D_1.push_back(keypoints1[match.queryIdx].pt);
        points2D_2.push_back(keypoints2[match.trainIdx].pt);
    }

}

std::vector<cv::DMatch> FeatureMatching::getMatches() {
    return goodMatches;
}

std::vector<cv::Point2f> FeatureMatching::get2Dpoints_1(){
    return points2D_1;
}

std::vector<cv::Point2f> FeatureMatching::get2Dpoints_2(){
    return points2D_2;
}