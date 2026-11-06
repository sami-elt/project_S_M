\# Marker Control Project



\## Overview



This project is a C++ application using OpenCV to detect and recognize a physical marker through a webcam.



The marker is a red four-sided shape with a black center.



When the marker is recognized, the application calculates its X and Y position in the camera image. The position is sent through UDP to Unity, where it controls the position of a sphere.



The complete pipeline is:



Camera -> Image Processing -> Marker Detection -> Marker Recognition -> X/Y Position -> UDP -> Unity



\## Components



\### CameraCapture



Handles the webcam input.



It opens the camera, captures frames and checks that the camera is available.



\### ImageProcessor



Processes the camera frames using OpenCV.



It creates grayscale and binary images that can be used during image processing and debugging.



\### MarkerDetector



Detects possible red marker candidates.



The image is converted to HSV color space and red areas are extracted using color masks.



Contours are detected and filtered using:



\- Four polygon corners

\- Minimum contour area

\- Convexity

\- Width/height ratio



\### MarkerRecognizer



Checks if a detected candidate is the correct marker.



The recognizer verifies that the red candidate contains the expected dark center.



\### UdpSender



Sends the recognized marker position from the C++ application to Unity using UDP.



The message format is:



X,Y



Example:



320,240



UDP communication uses localhost on port 5005.



\### Unity Visualization



Unity receives the marker coordinates through UDP.



The camera coordinates are converted to Unity coordinates and used to move a sphere.



Moving the physical marker left, right, up or down moves the sphere in the corresponding direction.



\## Requirements



\- Windows

\- C++17 compatible compiler

\- CMake

\- OpenCV

\- vcpkg

\- Visual Studio 2022

\- Webcam

\- Unity (for the visualization)



\## Build



Example using vcpkg:



```powershell

cmake -S . -B build -DCMAKE\_TOOLCHAIN\_FILE=C:/Users/<USER>/vcpkg/scripts/buildsystems/vcpkg.cmake



\#build the project:

cmake --build build --config Debug



\# Start the C++ application:

.\\build\\Debug\\app.exe



```



\## Unity



Open the `unity` directory as a Unity project.



Start the Unity scene and then start the C++ application.



Unity listens for UDP messages on port 5005.



When the marker is recognized, its X and Y coordinates control the sphere position.



\## Testing



The project has been tested with:



\- Webcam capture

\- Camera configuration and fallback

\- Image preprocessing

\- Red marker detection

\- Marker recognition

\- Horizontal marker movement

\- Vertical marker movement

\- UDP communication

\- Unity visualization

\- Clean Git clone, CMake configuration and build



Testing evidence is available in the `docs` directory.



\## Authors



\- Mohmad

\- Sami



