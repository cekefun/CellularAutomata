cmake_minimum_required(VERSION 3.8)
project(CellularAtuomata)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCL)

if(${OpenCL_FOUND})
    add_subdirectory(gpu)
endif()
