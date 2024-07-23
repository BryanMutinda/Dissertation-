#ifndef RESECTION_H
#define RESECTION_H

#include "functions_and_libs.h"

class Resection{
    private:
        // Containers
        //Images type
        cv::Mat rVector,
                rotationMatrix,
                previousRotationMatrix,
                previousTranslationVector, 
                tVector,
                distortion,
                kMatrix,
                poseCurrent,
                poseNext;

        // Vector Image type
        std::vector<cv::Mat> rotationMatrixVector,
                             translationVectorVector;

        // Float type
        double angle;
        std::vector<double>angles;

        // 3D points
        std::vector<cv::Point3f> points3D;

        void pnp();

    public:
        // Constructor
        Resection(const cv::Mat& kMatrix, const cv::Mat& distortion);

        void performResection(const std::vector<std::string>& images);
        
        // Get information
        std::vector<cv::Mat> getRotation();
        std::vector<cv::Mat> getTranslation();
        std::vector<double> getRotationAngle();
};
#endif // RESECTION_H