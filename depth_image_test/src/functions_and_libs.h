#ifndef FUNCTIONS_AND_LIBS_H
#define FUNCTIONS_AND_LIBS_H

// Opencv libraries
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// Bundle adjusment libs
#include <opencv2/stitching/detail/warpers.hpp>
#include <opencv2/viz.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/sfm.hpp>

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

// Creates a vector of string type that returns image names
std::vector<std::string> image_string_vector(const std::string& text, const std::string& imageType, const int& start, const int& stop);

// Visualise's the reprojection error on images
void visualise_reprojection_error(const std::vector<std::string>& textImages, const int& imageIterations, const cv::Mat& kMatrix, const cv::Size& imageSize);

void bundle_adjustment(const std::vector<std::string>& imageFiles, const cv::Size& imageSize);

#endif