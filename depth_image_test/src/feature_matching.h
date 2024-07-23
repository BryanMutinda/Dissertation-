#include "functions_and_libs.h"


class FeatureMatching {
private:
    // Containers 
    cv::Mat descriptors1, descriptors2;                     // descriptors
    std::vector<cv::KeyPoint> keypoints1, keypoints2;       // Keypoints
    std::vector<cv::Point2f> points2D_1, points2D_2;        // 2D points from goodMacthes
    std::vector<std::vector<cv::DMatch>> knnMatches;        // KNN matches between keys & descriptors
    std::vector<cv::DMatch> goodMatches;                    // matches after performing Lowe's ratio between keys & descriptors

public:
    // Constructor 
    FeatureMatching(const cv::Mat& descriptors1, const cv::Mat& descriptors2,
                    const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2);

    // Perform feature matching
    void match_features(const int& k, const float& ratio);
    
    // Return macthes
    std::vector<cv::DMatch> getMatches();

    // Return 2D points
    std::vector<cv::Point2f> get2Dpoints_1();
    std::vector<cv::Point2f> get2Dpoints_2();
};