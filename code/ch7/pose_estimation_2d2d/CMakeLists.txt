cmake_minimum_required(VERSION 3.5)
project(pose_est_2d2d)

set(CMAKE_CXX_STANDARD 11)

# opencv
find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(pose_est_2d2d pose_estimation_2d2d.cpp)
target_link_libraries(pose_est_2d2d ${OpenCV_LIBS})
