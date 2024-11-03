cmake_minimum_required(VERSION 3.22)
project(labwork_9_alyonka344)

set(CMAKE_CXX_STANDARD 14)

include_directories(allocator)

add_executable(labwork_9_alyonka344
        main.cpp
        allocator/Allocator.h)

add_subdirectory(Google_tests)