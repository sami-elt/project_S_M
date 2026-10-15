#pragma once

#include <opencv2/opencv.hpp>

class ImageProcessor
{
public:
    cv::Mat toGrayscale(const cv::Mat& image);
    cv::Mat applyThreshold(const cv::Mat& grayscale, int thresholdValue);
};