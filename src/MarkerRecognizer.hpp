#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class MarkerRecognizer
{
public:
    //bool för att ta emot hela bilden + punkter för fyrkant från markerdetector
    bool isTargetMarker(const cv::Mat& frame, const std::vector<cv::Point>& candidateContour);
};



