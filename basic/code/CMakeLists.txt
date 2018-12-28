cmake_minimum_required(VERSION 3.12)
project(basic)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/eigen3")

add_executable(basic main.cpp)