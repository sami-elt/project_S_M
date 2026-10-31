#include "MarkerDetector.hpp"

std::vector<std::vector<cv::Point>>
MarkerDetector::detectCandidates(const cv::Mat& binaryImage, const cv::Mat& colorImage)
{

    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> candidates;
    cv::Mat hsv;
   

    cv::cvtColor(colorImage, hsv, cv::COLOR_BGR2HSV);

    cv::Mat redMask1;
    cv::Mat redMask2;
    cv::Mat redMask;

    cv::inRange(
        hsv,
        cv::Scalar(0, 70, 50),
        cv::Scalar(10, 255, 255),
        redMask1
    );

    cv::inRange(
        hsv,
        cv::Scalar(170, 70, 50),
        cv::Scalar(180, 255, 255),
        redMask2
    );

    redMask = redMask1 | redMask2;
    cv:: imshow("RedMask", redMask);

    cv::findContours(
        redMask,
        contours,
        cv::RETR_EXTERNAL,
        cv::CHAIN_APPROX_SIMPLE
    );
    for (const auto& contour : contours)
    {
        std::vector<cv::Point> approx;

        double perimeter = cv::arcLength(contour, true);

        cv::approxPolyDP(
            contour,
            approx,
            0.02 * perimeter,
            true
        );
        cv::Rect box = cv::boundingRect(approx);

        double width = box.width;
        double height = box.height;
        double ratio = width / height;
  

       


        if (approx.size() == 4 &&
            cv::contourArea(approx) > 500 &&
            cv::isContourConvex(approx) &&
            ratio > 0.5 &&
            ratio < 2.0)
        {
        candidates.push_back(approx);
        }
    }

    return candidates;
}