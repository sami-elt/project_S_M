#include <opencv2/opencv.hpp>
#include <iostream>
#include "CameraCapture.hpp"

int main()
{
    cv::VideoCapture camera(0);

    if (!camera.isOpened())
    {
        std::cerr << "Could not open camera." << std::endl;
        return 1;
    }

    CameraCapture captureConfig;
    captureConfig.configureCamera(camera, 640, 480);

    cv::Mat emptyTestFrame;
    std::cout << "test with empty frame--should be 0--: "
              << captureConfig.isValidFrame(emptyTestFrame) << std::endl;

    cv::Mat frame;

    while (camera.read(frame))
    {   
        if (!captureConfig.isValidFrame(frame))
        {
            std::cerr << "invalid frame" << std::endl;
            break;
        }
        
        cv::imshow("camera capture", frame);

        if (cv::waitKey(20) == 27)
        {
            break;
        }
    }

    return 0;
}