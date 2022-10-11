cmake_minimum_required(VERSION 3.16)

project(frma LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(frma SHARED ${CMAKE_SOURCE_DIR}/src/perf_test_api.cpp)

SET(CMAKE_CXX_FLAGS "-std=c++11") 

add_executable(frma_test ${CMAKE_SOURCE_DIR}/tests/test.cpp)
target_link_libraries(frma_test frma)
