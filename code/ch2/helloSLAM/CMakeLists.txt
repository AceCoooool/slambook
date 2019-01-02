# 声明要求的 cmake 最低版本
cmake_minimum_required(VERSION 3.5)

# 声明一个 cmake 工程
project(helloSLAM)

# 采用C++11
set(CMAKE_CXX_STANDARD 11)

# 添加一个可执行程序
# 语法：add_executable( 程序名 源代码文件 ）
add_executable(helloSLAM helloSLAM.cpp)


