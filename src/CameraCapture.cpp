#include "CameraCapture.hpp"

void CameraCapture::configureCamera(cv::VideoCapture& camera, int width, int height)
{
    camera.set(cv::CAP_PROP_FRAME_WIDTH, width);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

bool CameraCapture::isValidFrame(const cv::Mat& frame)
{
    return !frame.empty() && frame.channels() == 3;
}