#ifndef RESECTION_H
#define RESECTION_H

#include "functions_and_libs.h"

class Resection{
    private:
        // Containers
        std::vector<int> previousImageMatchIdx, nextImageMatchIdx;      // Stores matches of previous of next image
        std::vector<int> matches; 
        std::vector<cv::DMatch> pair1, pair2;                           // Stores pairs of matches
        std::vector<cv::Point2f> points2DMatch;                         // 2D points from matches
        std::vector<cv::Point3f> points3D, points3DMatch;               // 3D points used previously and extracted from matches
        std::vector<int> matchesClean;                                  // matches with no duplicates
        std::vector<cv::Point3f> points3DClean;                         // 3D points with no matches
        std::vector<cv::KeyPoint> keypointsImage;                       // keypoints used to extract 2D points
        cv::Mat rVector, tVector;                                       // Store rotation & translation vectors
        cv::Mat rMatrix;                                                // Stores rotation matrix



    public:
        // Constructor
        Resection(const std::vector<cv::DMatch>& pair1, const std::vector<cv::DMatch>& pair2,
                     const std::vector<cv::Point3f>& points3D, const std::vector<cv::KeyPoint>& keypointsImage);

        // Extract 2D & 3D matches from respective match pairs
        void match_matches();

        // Obtain roation & translation matrices
        void performResection(const cv::Mat& kMatrix,const cv::Mat& distortion);
        
        // Get information
        cv::Mat getRotation();
        cv::Mat getRotationVector();
        cv::Mat getTranslation();
        std::vector<cv::Point2f> get2Dpoints();
        std::vector<cv::Point3f> get3Dpoints();
};
#endif // RESECTION_H