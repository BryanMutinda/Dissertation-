#include "epipolar_geometry.h"

// Constructor
EpipolarGeometry::EpipolarGeometry(const std::vector<cv::DMatch>& matches,
                                   const std::vector<cv::Point2f>& points2D_1, const std::vector<cv::Point2f>& points2D_2,
                                   const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, 
                                   const cv::Mat& image1, const cv::Mat& image2,
                                   const cv::Mat& kMatrix)
    : matches(matches), points2D_1(points2D_1), points2D_2(points2D_2), keypoints1(keypoints1), keypoints2(keypoints2),
      image1(image1), image2(image2), kMatrix(kMatrix) {}

// Calculate Essential matrix and retrieve Rotation & Translation
void EpipolarGeometry::perform_epipolar_geometry(const double& maxPixelDist, const double& confidence) {
    // Empty RANSAC mask variable
    std::vector<uchar> maskRANSAC(points2D_1.size());                 

    // RANSAC max distance is the maximum distance from a point to the epipolar line
    // (in pixels) beyond which the point is considered an outlier
    // confidence is ranged between 0 and 1 and tells the algorithm how many times to iterate
    essential = cv::findEssentialMat(points2D_1, points2D_2, kMatrix, cv::RANSAC, confidence, maxPixelDist, maskRANSAC);

    // Create inliers using RANSAC mask
    for (size_t i = 0; i < maskRANSAC.size(); i++) {
        if (maskRANSAC[i]) {
            inliers_1.push_back(points2D_1[i]);
            inliers_2.push_back(points2D_2[i]);
            ransacMatches.push_back(matches[i]);
        }
    }

    // Recover Rotation & Translation from Image 1 -> Image 2 
    cv::recoverPose(essential, inliers_1, inliers_2, kMatrix, rMatrix, tVector);
}

cv::Mat EpipolarGeometry::getRotation() {
    return rMatrix;
}

cv::Mat EpipolarGeometry::getTranslation() {
    return tVector;
}

std::vector<cv::Point2f> EpipolarGeometry::getInliers_1() {
    return inliers_1;
}

std::vector<cv::Point2f> EpipolarGeometry::getInliers_2() {
    return inliers_2;
}

void EpipolarGeometry::displayRotation() {
    std::cout << "Rotation Matrix:\n" << rMatrix << std::endl;
}

void EpipolarGeometry::displayTranslation() {
    std::cout << "Translation Matrix:\n" << tVector << std::endl;
}

void EpipolarGeometry::displayRansacMatches() {
    std::cout << "Matches: \n" 
              << "Number of matches before RANSAC: " << matches.size() << "\n"
              << "Number of matches after RANSAC: " << inliers_1.size() << std::endl;
}

void EpipolarGeometry::beforeRANSAC(const int& width, const int& height) {
    // Display matches
    cv::namedWindow("Before RANSAC", cv::WINDOW_NORMAL);
    cv::resizeWindow("Before RANSAC", width, height);
    cv::drawMatches(image1, keypoints1, image2, keypoints2, matches, imageMatch);
    cv::imshow("Before RANSAC", imageMatch);
    cv::waitKey(0); // Wait for a key press
    cv::destroyWindow("Before RANSAC"); // Destroy the window
}

void EpipolarGeometry::afterRANSAC(const int& width, const int& height) {
    // Display matches
    cv::namedWindow("After RANSAC", cv::WINDOW_NORMAL);
    cv::resizeWindow("After RANSAC", width, height);
    cv::drawMatches(image1, keypoints1, image2, keypoints2, ransacMatches, imageMatchR);
    cv::imshow("After RANSAC", imageMatchR);
    cv::waitKey(0); // Wait for a key press
    cv::destroyWindow("After RANSAC"); // Destroy the window
}
