cmake_minimum_required(VERSION 3.5)
project(g2o_curve_fitting)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

# 寻找G2O
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIR} "/usr/include/eigen3")

# OpenCV
find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_DIRS})

add_executable(curve_fitting main.cpp)
# 与G2O和OpenCV链接
target_link_libraries(curve_fitting ${OpenCV_LIBS} ${G2O_CORE_LIBRARY} ${G2O_STUFF_LIBRARY})
