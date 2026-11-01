#include <opencv2/opencv.hpp>
#include <iostream>
#include "CameraCapture.hpp"
#include "MarkerDetector.hpp"
#include "ImageProcessor.hpp"
#include "MarkerRecognizer.hpp"
#include "UdpSender.hpp"
#include <chrono>

int main()
{
    // Open the default camera
    cv::VideoCapture camera(0);

    // Check if the camera opened correctly
    if (!camera.isOpened())
    {
        std::cerr << "Could not open camera." << std::endl;
        return 1;
    }

    // Create the project components
    CameraCapture captureConfig;
    ImageProcessor processor;
    MarkerDetector detector;
    MarkerRecognizer recognizer;
    UdpSender sender;
    int requestedWidth = 1234;
    int requestedHeight = 777;

    if (!sender.initialize("127.0.0.1", 5005))
    {
        std::cerr << "Could not initialize UDP sender." << std::endl;
        return 1;
    }
    

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
    
    auto lastSendTime = std::chrono::steady_clock::now();
    while (camera.read(frame))
    {   
        
       bool markerFound = false;

        if (!captureConfig.isValidFrame(frame))
        {
            std::cerr << "invalid frame" << std::endl;
            break;

        }

        // Convert the camera frame to grayscale and binary
        cv::Mat gray = processor.toGrayscale(frame);
        cv::Mat binary = processor.applyThreshold(gray, 128);

        // Find possible marker candidates
        auto candidates = detector.detectCandidates(binary, frame);

        std::cout << "Candidates: " << candidates.size() << std::endl;

        for (const auto& candidate : candidates)
        {
           

            if (!recognizer.isTargetMarker(frame, candidate))
            {
                continue;
            }
            markerFound = true;
            cv::polylines(frame, candidate, true, cv::Scalar(0, 255, 0), 2);

            // Find the center position of the detected marker
            cv::Rect box = cv::boundingRect(candidate);

            cv::Point center(
                box.x + box.width / 2,
                box.y + box.height / 2
            );

            std::string message =
            std::to_string(center.x) + "," +
            std::to_string(center.y);

            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - lastSendTime
            ).count();

            if (elapsed >= 50)
            {
                sender.sendMessage(message);
                lastSendTime = now;
            }
            
            std::cout << "Sending marker position: "
            << message << std::endl;

          

            // Check the horizontal marker position
              std::string position;
            if (center.x < frame.cols / 3)
            {
                position = "LEFT";
            }
            else if (center.x > (frame.cols * 2) / 3)
            {
                position = "RIGHT";
            }
            else
            {
                position = "CENTER";
            }

            // Check the vertical marker position
            std :: string verticalPosition;
            if (center.y < frame.rows / 3)
            {
                verticalPosition = "TOP";
            }
            else if (center.y > (frame.rows * 2) / 3)
            {
                verticalPosition = "BOTTOM";
            }
            else
            {
                verticalPosition = "CENTER";
            }

            cv::putText(frame, position, cv::Point(30,50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, verticalPosition, cv::Point(30,100), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
            
            cv::circle(
                frame,
                center,
                20,
                cv::Scalar(255, 0, 255),
                -1
            );

           
        }

       if (!markerFound)
       {
           sender.sendMessage("NO_MARKER");
       }
        
        cv::imshow("camera capture", frame);
        cv::imshow("Binary", binary);

       
        
        if (cv::waitKey(20) == 27)
        {
            break;
        }
    }

    return 0;
}