#ifndef FUNCTIONS_AND_LIBS_H
#define FUNCTIONS_AND_LIBS_H

// Opencv libraries
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/calib3d.hpp>

// General Libraries
#include <string> 
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cmath>

// Headers
#include "image_conversion.h"
#include "epipolar_geometry.h"
#include "feature_detect.h"
#include "feature_matching.h"
#include "triangulation.h"
#include "resection.h"

// Functions
// Creates Pose Matrix
cv::Mat poseMatrix(const cv::Mat& K, const cv::Mat& R, const cv::Mat& t, bool returnPose);

// Creates depthmap
void createDepthMap(const cv::Size& imageSize, const cv::Mat& k, const std::vector<cv::Point3f>& pts3D, const bool& view);

// Saves points to be viewed by MeshLab
void save_points3d(const std::vector<cv::Point3f>& pts3D, const std::string& filename);

// Converts Rotation MAtrix to angle in degrees 
double rMatrix_2_angle(const cv::Mat& rMatrix);

// Superimpose images
void superimpose_images(const std::string& image1S, const std::string& image2S, const cv::Mat& rMatrix,
                        const cv::Mat& tVector, const int& width, const int& height, const std::string& title);

void superimpose_images_similar(const std::string& imageString, const cv::Mat& rMatrixData, const cv::Mat& rMatrixCode, 
                        const int& width, const int& height, const std::string& title);

// Calculates reprojection error
double reprojection_error(const cv::Mat& pose, const std::vector<cv::Point2f>& pts2D, const std::vector<cv::Point3f>& pts3D, 
                        const bool& average, const bool& view, const std::string& title);

// Creates a vector of string type that returns image names
std::vector<std::string> image_string_vector(const std::string& text, const std::string& imageType, const int& start, const int& stop);

// Calculates reprojection for multiple images
void reprojection_errors_multiple_images(int startImage, int endImage, const cv::Mat& kMatrix, const cv::Mat& distortion);

#endif