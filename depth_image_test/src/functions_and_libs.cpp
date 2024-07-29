#include "functions_and_libs.h"


/* ==================================================================================================================== 
                                The function returns the Pose Matrix
======================================================================================================================= */

cv::Mat poseMatrix(const cv::Mat& K, const cv::Mat& R, const cv::Mat& t, bool returnPose){
    cv::Mat pose = cv::Mat::eye(3, 4, CV_64F);
    // Add rotation matrix to pose matrix
    R.copyTo(pose(cv::Rect(0, 0, 3, 3)));
    // Add the translation vector t to the pose matrix
    t.copyTo(pose.col(3));

    // if true returns P = K * pose
    if (returnPose){
        return K * pose;
    }
    // if not true returns the pose alone
    else{
        return pose;
    }
}

/* ==================================================================================================================== 
                                The function visualise the depth map in a 2D plane 
======================================================================================================================= */

void createDepthMap(const cv::Size& imageSize, const cv::Mat& k, const std::vector<cv::Point3f>& pts3D, const bool& view){    
    // Create a blank depth map (initialized to zeros)
    cv::Mat depthMap(imageSize, CV_64F, cv::Scalar(0));

    // Project 3D points to 2D image plane
    for (const auto& point : pts3D) {
        // Convert 3D point to homogeneous coordinates
        cv::Mat point3D_h = (cv::Mat_<double>(4, 1) << point.x, point.y, point.z, 1.0);

        // Project the 3D point to 2D
        cv::Mat point2D_h = k * point3D_h(cv::Range(0, 3), cv::Range::all());

        // Normalize the projected point
        cv::Point2f point2D(point2D_h.at<double>(0) / point2D_h.at<double>(2),
                            point2D_h.at<double>(1) / point2D_h.at<double>(2));

        // Set the depth value in the depth map
        int x = static_cast<int>(point2D.x);
        int y = static_cast<int>(point2D.y);

        // Ensure the point is within the image bounds
        if (x >= 0 && x < depthMap.cols && y >= 0 && y < depthMap.rows) {
            depthMap.at<double>(y, x) = point.z;
        }
    }

    if (view){
        // Normalize the depth map for visualization (optional)
        cv::normalize(depthMap, depthMap, 0, 255, cv::NORM_MINMAX, CV_8U);

        // Display the depth map
        cv::namedWindow("Depth Map", cv::WINDOW_NORMAL);
        cv::resizeWindow("Depth Map", 1200, 800); // Resize the window to 1200x800 pixels
        cv::imshow("Depth Map", depthMap);
        cv::waitKey(0);
        cv::destroyAllWindows();

    }
}

/* ============================================================================================================ 
The function saves 3D points from triangulation to a .ply file to be visualised using 3D software being MeshLab
=============================================================================================================== */

void save_points3d(const std::vector<cv::Point3f>& pts3D, const std::string& filename){
    std::ofstream file;
    file.open(filename);

    file << "ply\n";
    file << "format ascii 1.0\n";
    file << "element vertex " << pts3D.size() << "\n";
    file << "property float x\n";
    file << "property float y\n";
    file << "property float z\n";
    file << "end_header\n";

    for (const auto& pt : pts3D) {
        file << pt.x << " " << pt.y << " " << pt.z << "\n";
    }

    std::cout << "\nSaved" << filename << "\n";

    file.close();
}

/*=============================================================================================================
                        Converts Matrix to Angle in Degrees using Rodgrigues (Pg 647 - 648)
===============================================================================================================*/

double rMatrix_2_angle(const cv::Mat& rMatrix) {
    // Using Rodrigues to convert Matrix to Vector
    cv::Vec3d vector;
    cv::Rodrigues(rMatrix, vector);

    // Convert vector to angle in Degrees
    double angle = cv::norm(vector) * (180.0 / CV_PI);
    return angle;
}


/*=============================================================================================================
                        Function creates numbered strings in a string vector
===============================================================================================================*/
std::vector<std::string> image_string_vector(const std::string& text, const std::string& imageType, const int& start, const int& stop){
    // Containers
    std::string filename;                               // filename
    std::vector<std::string> vectorString;             // Vector output

    // Loop and create vector
    for (int i = start; i < stop + 1; i++){
        filename = text + std::to_string(i) + imageType;
        vectorString.push_back(filename);
    }

    return vectorString;
}