cmake_minimum_required(VERSION 3.15)

project(HideCppBanking)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all .cpp files automatically
file(GLOB SOURCES
     "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Create executable
add_executable(HideCppBanking ${SOURCES})
