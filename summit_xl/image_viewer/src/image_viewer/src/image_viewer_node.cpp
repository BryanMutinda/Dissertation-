#include <iostream>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        // Convert the ROS image message to an OpenCV image
        cv::Mat image = cv_bridge::toCvShare(msg, "bgr8")->image;
        // Display the image using OpenCV
        cv::imshow("View Image", image);
        cv::waitKey(30);  // Add a short delay to allow for image rendering
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

int main(int argc, char** argv) {
    // Initialize the ROS node
    ros::init(argc, argv, "image_subscriber_node");

    // Create a ROS node handle
    ros::NodeHandle nh;

    // Subscribe to the image topic
    ros::Subscriber sub = nh.subscribe("/robot/front_rgbd_camera/rgb/image_raw", 1, imageCallback);

    // Enter a loop, pumping callbacks
    ros::spin();

    return 0;
}
