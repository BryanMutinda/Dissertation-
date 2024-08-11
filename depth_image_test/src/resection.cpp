#include "functions_and_libs.h"

// Constructor
Resection::Resection(const std::vector<cv::DMatch>& pair1, const std::vector<cv::DMatch>& pair2,
                     const std::vector<cv::Point3f>& points3D, const std::vector<cv::KeyPoint>& keypointsImage)
                    : pair1(pair1), pair2(pair2), points3D(points3D), keypointsImage(keypointsImage) {}


void Resection::match_matches(){
    // clear containers
    previousImageMatchIdx.clear();
    nextImageMatchIdx.clear();
    matches.clear();
    points3DMatch.clear();
    points2DMatch.clear();
    matchesClean.clear();
    points3DClean.clear();

    // Extract second column from first pair of matches
    for (const cv::DMatch& matchPrev : pair1){
        previousImageMatchIdx.push_back(matchPrev.trainIdx);    // trainIdx is second column e.g. image2 matches from image 1 -> 2 match pair
    }

    // Extract first column from second pair of matches
    for (const cv::DMatch& matchNext : pair2){
        nextImageMatchIdx.push_back(matchNext.queryIdx);        // queryIdx is first column e.g. image3 matches from image 2 -> 3 match pair
    }


    // Check for matches between second column of first pair and first column of second pair
    for (int i = 0; i < previousImageMatchIdx.size(); i++){
        for (int j = 0; j < nextImageMatchIdx.size(); j++){
            if (previousImageMatchIdx[i] == nextImageMatchIdx[j]){
                matches.push_back(pair2[j].trainIdx);
                points3DMatch.push_back(points3D[i]);
            }
        }
    }

    std::cout << "\nMatches before remove duplicates: " <<matches.size();

    // remove duplicates
    for (size_t k = 0; k < matches.size(); ++k) {
        bool matchExists = false;
        for (size_t l = 0; l < matchesClean.size(); ++l) {
            if (matches[k] == matchesClean[l]) {
                matchExists = true;
                break;
            }
        }
        if (!matchExists) {
            matchesClean.push_back(matches[k]);
            points3DClean.push_back(points3DMatch[k]);
        }
    }

    std::cout << "\nMatches after remove duplicates: " <<matchesClean.size();
   
    // Create 2D points that are based from matches
    for (const int& match : matchesClean) {
        points2DMatch.push_back(keypointsImage[match].pt);
    }
}


// Perform resection
void Resection::performResection(const cv::Mat& kMatrix,const cv::Mat& distortion){
    
    // Create rotation and translation vectors using PnP Pg 647 - 648
    cv::solvePnP(points3DClean, points2DMatch, kMatrix, distortion, rVector, tVector);

    // Using Rodrigues to converts rotation vector to rotation matrix
    cv::Rodrigues(rVector, rMatrix);

}  

// return rotation matrix
cv::Mat Resection::getRotation(){
    return rMatrix;
}

// return rotation vector
cv::Mat Resection::getRotationVector(){
    return rVector;
}

// return translation
cv::Mat Resection::getTranslation(){
    return tVector;
}

// return respective 2D points
std::vector<cv::Point2f> Resection::get2Dpoints(){
    return points2DMatch;
}

// return respective 3D points
std::vector<cv::Point3f> Resection::get3Dpoints(){
    return points3DClean;
}
