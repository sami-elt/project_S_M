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
    int requestedWidth = 1234;
    int requestedHeight = 777;

    int fallbackWidth = 640;
    int fallbackHeight = 480;

    bool configurationOk =
        captureConfig.configureCamera(camera, requestedWidth, requestedHeight);

    if (!configurationOk)
    {
        std::cerr << requestedWidth << "x" << requestedHeight << " is not supported." << std::endl;
        std::cout << "Trying fallback resolution " << fallbackWidth << "x" << fallbackHeight << "..." << std::endl;

        configurationOk =
            captureConfig.configureCamera(camera, fallbackWidth, fallbackHeight);

         if (!configurationOk)
        {
            std::cerr << "Could not configure camera." << std::endl;
            return 1;
        }

        std::cout << "Fallback successful: " << fallbackWidth << "x" << fallbackHeight << std::endl;
    }

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