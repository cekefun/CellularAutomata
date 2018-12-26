cmake_minimum_required(VERSION 3.8)

include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

add_executable(OpenCLTest main.cpp)
target_include_directories (OpenCLTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (OpenCLTest ${OpenCL_LIBRARY})
