cmake_minimum_required(VERSION 3.14)
project(buffer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(buffer)
add_subdirectory(googletest)

add_executable(bufferTests tests/bufferTests.cpp)
target_link_libraries(bufferTests PUBLIC 
    buffer
    gtest_main
)

target_compile_options(bufferTests PUBLIC -std=c++20 -Wall -Wextra -O3)