cmake_minimum_required(VERSION 2.8)

project(frma LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(frma SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/perf_test_api.cpp)

set_target_properties(frma PROPERTIES CXX_STANDARD 11) 

add_executable(frma_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)
target_link_libraries(frma_test frma)
