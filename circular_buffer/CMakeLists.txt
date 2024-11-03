cmake_minimum_required(VERSION 3.22)
project(labwork_8_alyonka344)

set(CMAKE_CXX_STANDARD 20)

add_executable(labwork_8_alyonka344
        main.cpp
        CCircularBuffer/CCircularBuffer.h
        CCircularBufferExt/CCircularBufferExt.h)

add_subdirectory(Google_tests)
