cmake_minimum_required(VERSION 3.10)
project(MyFirstVision)

# magic switch: let CMake generate the compile command list!
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED COMPONENTS core highgui videoio imgproc)
add_executable(WebcamTest main.cpp)
target_link_libraries(WebcamTest ${OpenCV_LIBS})
