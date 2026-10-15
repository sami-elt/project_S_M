#include <opencv2/opencv.hpp>
#include <iostream>
#include "ImageProcessor.hpp"

int main()
{
    cv::VideoCapture camera(0);

    if (!camera.isOpened())
    {
        std::cerr << "Could not open camera." << std::endl;
        return 1;
    }

    ImageProcessor processor;
    cv::Mat frame;

    while (camera.read(frame))
    {   // Gör bilden grå
        cv::Mat gray = processor.toGrayscale(frame);
        //  Gör gråbilden svart/vit
        cv::Mat binary = processor.applyThreshold(gray, 120);

        cv::imshow("Original", frame);
        cv::imshow("Grayscale", gray);
        cv::imshow("Binary", binary);

        if (cv::waitKey(20) == 27)
        {
            break;
        }
    }

    return 0;
}