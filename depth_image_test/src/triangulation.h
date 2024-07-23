#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "functions_and_libs.h"

class Triangulation {
private:
    // Containers
    std::vector<cv::Point2f> inlier1, inlier2;  // Inliers points 
    cv::Mat pose1, pose2;                       // pose1, pose2 matrices
    std::vector<cv::Point3f> points3D;          // 3D coordinates from 4D  
    cv::Mat points4D;                               

public:
    // Constructor
    Triangulation(const cv::Mat& pose1, const cv::Mat& pose2, 
                  const std::vector<cv::Point2f>& inlier1, const std::vector<cv::Point2f>& inlier2);

    // Peform triangulation
    void perform_triangulation();

    // Return 3D points
    std::vector<cv::Point3f> get3Dpoints();
};

#endif // TRIANGULATION_H