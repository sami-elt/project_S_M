#pragma once

#include <opencv2/opencv.hpp>

class CameraCapture
{
public:
    void configureCamera(cv::VideoCapture& camera, int width, int height);
    bool isValidFrame(const cv::Mat& frame);
};