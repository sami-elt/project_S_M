#include "ImageProcessor.hpp"

cv::Mat ImageProcessor::toGrayscale(const cv::Mat& image)
{
    cv::Mat gray;

    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    return gray;
}
cv::Mat ImageProcessor::applyThreshold(const cv::Mat& grayscale, int thresholdValue)
{
    cv::Mat binary;
    cv::threshold(grayscale, binary, thresholdValue, 255, cv::THRESH_BINARY);
    return binary;
}
    