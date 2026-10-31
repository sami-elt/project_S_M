#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class MarkerDetector
{
public:
    std::vector<std::vector<cv::Point>> detectCandidates(
    const cv::Mat& binaryImage,
    const cv::Mat& colorImage
);
};