cmake_minimum_required(VERSION 3.5)
project(direct_semidense)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

# 添加cmake模块路径
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

# opencv
find_package(OpenCV 3 REQUIRED)
find_package(G2O REQUIRED)
find_package(CSparse REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${G2O_INCLUDE_DIR} ${CSPARSE_INCLUDE_DIR} "/usr/include/eigen3")

add_executable(direct_semidense direct_semidense.cpp)
target_link_libraries(direct_semidense ${OpenCV_LIBS} ${G2O_CORE_LIBRARY} ${CSPARSE_LIBRARY} ${G2O_STUFF_LIBRARY}
        ${CSPARSE_LIBRARY} g2o_types_sba g2o_csparse_extension)
