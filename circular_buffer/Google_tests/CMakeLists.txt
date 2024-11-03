project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Buffer_Tests CircularBufferTests.cpp CircularBufferExtTests.cpp)

target_link_libraries(Buffer_Tests gtest gtest_main)