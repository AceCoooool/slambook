cmake_minimum_required(VERSION 3.5)
project(triangulation)

set(CMAKE_CXX_STANDARD 11)

# opencv
find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(triangulation triangulation.cpp)
target_link_libraries(triangulation ${OpenCV_LIBS})
