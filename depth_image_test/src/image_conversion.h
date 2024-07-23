#ifndef IMAGE_CONVERSION_H
#define IMAGE_CONVERSION_H

#include "functions_and_libs.h"

class ImageConversion {
public:
    // Constructor
    ImageConversion(const std::string& imageText);

    // Converts image to grey
    void convert2gray();

    // Returns grey image
    cv::Mat getGreyImage();

private:
    // Containers
    cv::Mat imageGrey, imageColour;             // Image Containers
    std::string imageText;                      // Image file path
};

#endif // IMAGE_CONVERSION_H
