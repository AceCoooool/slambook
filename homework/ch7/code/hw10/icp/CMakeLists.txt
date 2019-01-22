cmake_minimum_required(VERSION 3.5)
project(hw10_2)

set(CMAKE_CXX_STANDARD 11)

# opencv
find_package(OpenCV 3 REQUIRED)
find_package(Ceres REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${CERES_INCLUDE_DIRS} "/usr/include/eigen3")


add_executable(hw10_2 hw10_2.cpp)
target_link_libraries(hw10_2 ${OpenCV_LIBS} ${CERES_LIBRARIES})
