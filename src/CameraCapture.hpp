#pragma once

#include <opencv2/opencv.hpp>

class CameraCapture
{
public:
    bool configureCamera(cv::VideoCapture& camera, int width, int height);
    bool isValidFrame(const cv::Mat& frame);
};