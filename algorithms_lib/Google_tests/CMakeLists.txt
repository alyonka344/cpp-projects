project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Algorithms_Tests AlgorithmsTests.cpp)

target_link_libraries(Algorithms_Tests gtest gtest_main)