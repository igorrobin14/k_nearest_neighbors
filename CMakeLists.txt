# CMake minimum version required
cmake_minimum_required(VERSION 3.5)

# Project name and type
project(knn_images C)

# Set source files
file(GLOB_RECURSE SOURCE_FILES src/*.c)

# Set include directories
include_directories(include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link math library
target_link_libraries(${PROJECT_NAME} m)

# Link jpeg library
target_link_libraries(${PROJECT_NAME} jpeg)

# Add optimization flags
target_compile_options(${PROJECT_NAME} PRIVATE -Ofast -g)
