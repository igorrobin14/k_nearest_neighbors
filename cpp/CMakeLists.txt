cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(KNearestNeighbors VERSION 0.1)

# Set source files
file(GLOB SOURCES src/*.cpp main.cpp)

# Set include directories
include_directories(include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} m jpeg)

# Add optimization flags
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g) # add optimizaion in the future

# Add custom command
add_custom_target(launch COMMAND ./KNearestNeighbors DEPENDS KNearestNeighbors WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Launching KNearestNeighbors for images")

