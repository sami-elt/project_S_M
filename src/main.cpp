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
    bool configurationOk = captureConfig.configureCamera(camera, 1234, 777);

    if (!configurationOk)
    {
        std::cerr << "WARNING: Camera could not use the requested resolution."
              << std::endl;
    }
    std::cout << "Requested resolution: 1234x777" << std::endl;

    std::cout << "Actual resolution: "
          << camera.get(cv::CAP_PROP_FRAME_WIDTH)
          << "x"
          << camera.get(cv::CAP_PROP_FRAME_HEIGHT)
          << std::endl;

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