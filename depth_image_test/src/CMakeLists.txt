cmake_minimum_required(VERSION 3.16.3)

# Project name
project(depth_image)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Compile as C++11
add_compile_options(-std=c++17)

# Set the path to OpenCV directory
set(OpenCV_DIR "/home/bryan/programs/opencv/build")

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include the OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Executables
add_executable(${PROJECT_NAME} 
    image_conversion.cpp
    epipolar_geometry.cpp
    feature_detect.cpp
    feature_matching.cpp
    functions_and_libs.cpp
    main.cpp
    triangulation.cpp
    resection.cpp
    dataset.cpp
)

# Link the OpenCV libraries to your executable
target_link_libraries(${PROJECT_NAME} 
    ${OpenCV_LIBS}
)
