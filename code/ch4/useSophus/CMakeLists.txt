cmake_minimum_required(VERSION 3.5)
project(useSophus)

# 为使用 sophus, 您需要使用find_package命令找到它
# 注: 使用sophus, 会自动帮你寻找到eigen3的头文件
find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

add_executable(useSophus useSophus.cpp)
target_link_libraries(useSophus ${Sophus_LIBRARIES})

