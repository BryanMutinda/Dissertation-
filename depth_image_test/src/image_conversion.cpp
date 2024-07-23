#include "functions_and_libs.h"

// Constructor
ImageConversion::ImageConversion(const std::string& imageText) : imageText(imageText) {}

// Converts image to grey
void ImageConversion::convert2gray() {
    // Load the image in colour
    imageColour = cv::imread(imageText, cv::IMREAD_COLOR);
    if (imageColour.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return;
    }

    // Convert to grayscale
    cv::cvtColor(imageColour, imageGrey, cv::COLOR_BGR2GRAY);
    
    // Check if the grayscale image is empty
    if (imageGrey.empty()) {
        std::cerr << "Error: The grayscale image is empty." << std::endl;
    }
}

// Returns the converted grey image
cv::Mat ImageConversion::getGreyImage(){
    return imageGrey;
}
