cmake_minimum_required(VERSION 3.5)
project(visualizeGeometry)

set(CMAKE_CXX_STANDARD 11)

# 添加Eigen头文件
include_directories("/usr/include/eigen3")

# 添加Pangolin依赖
find_package(Pangolin)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(visualizeGeometry visualizeGeometry.cpp)
target_link_libraries(visualizeGeometry ${Pangolin_LIBRARIES})
