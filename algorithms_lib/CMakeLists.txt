cmake_minimum_required(VERSION 3.22)
project(labwork_11_alyonka344)

set(CMAKE_CXX_STANDARD 14)

add_executable(labwork_11_alyonka344
        main.cpp
        Algorithms/Algorithms.h
        Algorithms/AdditionalClasses/XRangeClass.h
        Algorithms/xrange.h
        Algorithms/zip.h
        Algorithms/AdditionalClasses/ZipClass.h)

add_subdirectory(Google_tests)