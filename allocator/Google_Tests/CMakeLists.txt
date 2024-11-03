project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(AllocatorTests AllocatorTests.cpp)

target_link_libraries(AllocatorTests gtest gtest_main)