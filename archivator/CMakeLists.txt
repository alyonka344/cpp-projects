cmake_minimum_required(VERSION 3.22)
project(labwork_4_alyonka344)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)

add_executable(labwork_4_alyonka344
        bin/main.cpp
        lib/archivator.cpp
        lib/archivator.h
        lib/HammingCode.cpp
        lib/HammingCode.h
        lib/Parser.cpp
        lib/Parser.h)
