#include "CameraCapture.hpp"

bool CameraCapture::configureCamera(cv::VideoCapture& camera, int width, int height)
{
    camera.set(cv::CAP_PROP_FRAME_WIDTH, width);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, height);

    int actualWidth = static_cast<int>(camera.get(cv::CAP_PROP_FRAME_WIDTH));
    int actualHeight = static_cast<int>(camera.get(cv::CAP_PROP_FRAME_HEIGHT));

    return actualWidth == width && actualHeight == height;
}

bool CameraCapture::isValidFrame(const cv::Mat& frame)
{
    return !frame.empty() && frame.channels() == 3;
}