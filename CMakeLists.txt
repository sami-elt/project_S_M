cmake_minimum_required(VERSION 3.16)
project(Helloworld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "C:/Users/samio/Desktop/opencv/build")

find_package(OpenCV REQUIRED)

add_executable(app 
src/main.cpp
src/CameraCapture.cpp)
target_link_libraries(app PRIVATE ${OpenCV_LIBS})
