cmake_minimum_required(VERSION 3.5)
project(hw10_1)

set(CMAKE_CXX_STANDARD 11)

# opencv
find_package(OpenCV 3 REQUIRED)
find_package(Ceres REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${CERES_INCLUDE_DIRS} "/usr/include/eigen3")


add_executable(hw10_1 hw10_1.cpp)
target_link_libraries(hw10_1 ${OpenCV_LIBS} ${CERES_LIBRARIES})
