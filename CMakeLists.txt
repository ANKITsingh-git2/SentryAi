cmake_minimum_required(VERSION 3.10)

project(SentryAI VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# 1. FIND the library on your system
find_package(CURL REQUIRED)

# 2. Add source files
add_executable(sentry-ai src/main.cpp src/file_reader.cpp src/http_client.cpp)

# 3. LINK the library to the executable
if(CURL_FOUND)
    target_link_libraries(sentry-ai CURL::libcurl)
    include_directories(${CURL_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Could not find libcurl. Please install it.")
endif()