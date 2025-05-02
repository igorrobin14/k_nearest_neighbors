cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(KNearestNeighbors VERSION 0.1)

# Set source files
file(GLOB SOURCES src/*.cpp main.cpp)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

# Set include directories
include_directories(include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} m jpeg ${wxWidgets_LIBRARIES})

# Add optimization flags
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g) # add optimizaion in the future

# Add custom command
add_custom_target(launch COMMAND ./KNearestNeighbors DEPENDS KNearestNeighbors WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Launching KNearestNeighbors for images")

