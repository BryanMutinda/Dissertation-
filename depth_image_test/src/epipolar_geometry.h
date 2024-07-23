#ifndef EPIPOLAR_GEOMETRY_H
#define EPIPOLAR_GEOMETRY_H

#include "functions_and_libs.h"

class EpipolarGeometry {
private:
    // Containers 
    std::vector<cv::DMatch> matches;                        // matches
    std::vector<cv::Point2f> points2D_1, points2D_2;        // image points
    std::vector<cv::KeyPoint> keypoints1, keypoints2;       // keypoints
    std::vector<cv::Point2f> inliers_1, inliers_2;          // image points after RANSAC
    cv::Mat kMatrix, rMatrix, tVector, essential;           // Camera Intrinsic, Rotation, Translation & Essential matrix
    cv::Mat image1, image2;                                 // Images
    cv::Mat imageMatch, imageMatchR;                        // Image to contain matches
    std::vector<cv::DMatch> ransacMatches;                  // Matches after outliers removed

public:
    // Constructor
    EpipolarGeometry(const std::vector<cv::DMatch>& matches,
                     const std::vector<cv::Point2f>& points2D_1, const std::vector<cv::Point2f>& points2D_2,
                     const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, 
                     const cv::Mat& image1, const cv::Mat& image2,
                     const cv::Mat& kMatrix);

    // Initialise
    void perform_epipolar_geometry(const double& maxPixelDist, const double& confidence);

    // Get information
    cv::Mat getRotation();
    cv::Mat getTranslation();
    std::vector<cv::Point2f> getInliers_1();
    std::vector<cv::Point2f> getInliers_2();

    // Display information
    void displayRotation();
    void displayTranslation();
    void displayRansacMatches();
    void beforeRANSAC(const int& width, const int& height);
    void afterRANSAC(const int& width, const int& height);
};

#endif // EPIPOLAR_GEOMETRY_H
