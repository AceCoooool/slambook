cmake_minimum_required(VERSION 3.5)
project(feature_extraction)

set(CMAKE_CXX_STANDARD 11)

# opencv
find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(feature_extraction feature_extraction.cpp)
target_link_libraries(feature_extraction ${OpenCV_LIBS})
