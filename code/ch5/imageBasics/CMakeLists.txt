cmake_minimum_required(VERSION 3.5)
project(imageBasics)

# 添加c++ 11标准支持
set(CMAKE_CXX_STANDARD 11)

# 寻找OpenCV库
find_package(OpenCV 3 REQUIRED)
# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(imageBasics imageBasics.cpp)
# 链接OpenCV库
target_link_libraries(imageBasics ${OpenCV_LIBS})
