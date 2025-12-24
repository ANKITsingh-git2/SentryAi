cmake_minimum_required(VERSION 3.10)

# Project Name and Version
project(SentryAI VERSION 1.0)

# Specify the C++ Standard (C++17 is great for modern file handling)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the 'src' directory to the build path
include_directories(include)

# Define the Executable
# We tell CMake: "Make an executable named 'sentry-ai' using 'src/main.cpp'"
add_executable(sentry-ai src/main.cpp)