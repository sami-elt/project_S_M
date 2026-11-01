#include "MarkerRecognizer.hpp"
#include <iostream>

bool MarkerRecognizer::isTargetMarker(const cv::Mat& frame, const std::vector<cv::Point>& candidateContour)
{

    //skapa en bounding box för klippa ut bilden runt konturen
    cv::Rect boundingBox = cv::boundingRect(candidateContour);

    //ser till att vår boundingbox är innanför gränserna
    if (boundingBox.x < 0 || boundingBox.y < 0 ||
        boundingBox.x + boundingBox.width > frame.cols ||
        boundingBox.y + boundingBox.height > frame.rows){
            return false;
        }

    //klipp ut bild
    cv::Mat imageCropped = frame(boundingBox);
    if (imageCropped.empty()) return false;


    cv::Mat gray, binary;
    cv::cvtColor(imageCropped, gray, cv::COLOR_BGR2GRAY);

    cv::threshold(gray, binary, 100,255, cv::THRESH_BINARY_INV);
    

    int marginX = boundingBox.width / 4;
    int marginY = boundingBox.height / 4;

    if (boundingBox.width <= marginX * 2 || boundingBox.height <= marginY * 2)
    {
        return false;
    }
    
    cv::Rect centerRegion(marginX, marginY, boundingBox.width - (marginX * 2), boundingBox.height - (marginY * 2));
    cv::Mat centerPixels = binary(centerRegion);

    // 4. Räkna hur mycket svart mönster (som nu är vita pixlar) vi hittade i mitten
    int nonZeroPixels = cv::countNonZero(centerPixels);
    int totalPixels = centerPixels.rows * centerPixels.cols;
    
    // Om mer än 15% av mitten är ett mörkt mönster, godkänner vi den som vår markör!
    double patternRatio = (double)nonZeroPixels / (double)totalPixels;
    std::cout << "Pattern ratio: " << patternRatio << std::endl;
    return (patternRatio > 0.60);
    
    


}
