cmake_minimum_required(VERSION 3.22)
project(labwork_3_alyonka344)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)

add_executable(labwork_3_alyonka344
        bin/main.cpp
        lib/sandpile.cpp
        lib/parser.cpp
        )

include_directories(bin)