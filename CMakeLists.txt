cmake_minimum_required(VERSION 3.15)

project(HideCppBanking)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the project's headers directory
include_directories(${PROJECT_SOURCE_DIR}/headers)

# Collect all .cpp files automatically from src and the project root (some .cpp files exist at repo root)
file(GLOB SOURCES
     "${PROJECT_SOURCE_DIR}/src/*.cpp"
     "${PROJECT_SOURCE_DIR}/*.cpp"
)

# Put the built executable into the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# Create executable
add_executable(final ${SOURCES})
