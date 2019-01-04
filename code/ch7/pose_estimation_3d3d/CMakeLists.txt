cmake_minimum_required(VERSION 3.5)
project(pose_estimation_3d3d)

set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

# opencv
find_package(OpenCV 3 REQUIRED)
find_package(G2O REQUIRED)
find_package(CSparse REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${G2O_INCLUDE_DIR} ${CSPARSE_INCLUDE_DIR} "/usr/include/eigen3")


add_executable(pose_estimation_3d3d pose_estimation_3d3d.cpp)
target_link_libraries(pose_estimation_3d3d ${OpenCV_LIBS} ${G2O_CORE_LIBRARY} ${CSPARSE_LIBRARY} ${G2O_STUFF_LIBRARY}
        ${CSPARSE_LIBRARY} g2o_types_sba g2o_csparse_extension)
