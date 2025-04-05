# CMake minimum version required
cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_STANDARD_REQUIRED True)

# Project name and type
project(knn_images C)

# Set source files
file(GLOB_RECURSE SOURCE_FILES src/*.c)

# Set include directories
include_directories(include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_compile_options(-std=c11)

# Link libraries
target_link_libraries(${PROJECT_NAME} m jpeg)

# Add optimization flags
target_compile_options(${PROJECT_NAME} PRIVATE -Ofast -g)

# Add custom command
add_custom_target(launch COMMAND ./knn_images DEPENDS knn_images WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Launching k-NN with images")
