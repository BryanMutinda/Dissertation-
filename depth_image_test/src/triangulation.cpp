#include "functions_and_libs.h"

// Constructor
Triangulation::Triangulation(const cv::Mat& pose1, const cv::Mat& pose2, 
                             const std::vector<cv::Point2f>& inlier1, const std::vector<cv::Point2f>& inlier2) :
                             pose1(pose1), pose2(pose2), inlier1(inlier1), inlier2(inlier2) {}


void Triangulation::perform_triangulation(){
    // Perform triangulation
    cv::triangulatePoints(pose1, pose2, inlier1, inlier2, points4D);
    //std::cout << points4D;

    // Homogeneous -> 3D   
    for (int i = 0; i < points4D.cols; i++) {
        cv::Mat x = points4D.col(i);

        // Normalize by the 4th value
        x /= x.at<float>(3);
        points3D.push_back(cv::Point3f(x.at<float>(0), x.at<float>(1), x.at<float>(2)));
    }
}

std::vector<cv::Point3f> Triangulation::get3Dpoints(){
    return points3D;
}