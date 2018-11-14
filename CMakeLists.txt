

cmake_minimum_required(VERSION 3.12)
project(OpenCLTest)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

add_executable(OpenCLTest gpu/main.cpp)
target_include_directories (OpenCLTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (OpenCLTest ${OpenCL_LIBRARY})
