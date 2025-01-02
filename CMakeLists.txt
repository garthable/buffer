cmake_minimum_required(VERSION 3.14)
project(SVector VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GOOGLE_TEST_VERSION 1.15.2)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v${GOOGLE_TEST_VERSION}.zip 
    FIND_PACKAGE_ARGS ${GOOGLE_TEST_VERSION}
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(sVector)

add_executable(sVectorTests tests/sVectorTests.cpp)
target_link_libraries(sVectorTests PUBLIC 
    sVector
    gtest_main
)

target_compile_options(sVectorTests PUBLIC -std=c++20 -Wall -Wextra -O3)