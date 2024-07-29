#include "functions_and_libs.h"

std::pair<std::vector<int>, std::vector<int>> create_subset(const std::vector<cv::DMatch>& matches){
    // Containers
    std::vector<int> column1, column2;
    std::pair<std::vector<int>, std::vector<int>> pairs;

    // loop through matches
    for (auto match : matches){
        column1.push_back(match.queryIdx);
        column2.push_back(match.trainIdx);
    }

    // Make pair
    pairs = std::make_pair(column1, column2);
    
    return pairs;
}

std::vector<int> match_matches(const std::vector<cv::DMatch>& pair1, const std::vector<cv::DMatch>& pair2){
    // Containers
    std::vector<int> pair1_int, pair2_int, matches;


    // Create subsets
    pair1_int = create_subset(pair1);
    pair2_int = create_subset(pair2);

    // Check for matches between second column of first pair and first column of second pair
    for (auto matchPair1 : pair1_int.second ){
        for (auto matchPair2 : pair2_int.first){
            if (matchPair1 == matchPair2){
                matches.push_back(matchPair2);
            }
        }
    }
    
    
}

std::vector<cv::Point2f> create