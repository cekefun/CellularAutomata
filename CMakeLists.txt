cmake_minimum_required(VERSION 3.8)
project(CellularAtuomata)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

ENABLE_TESTING()

option(USE_SYSTEM_GTEST "Use the google test framework installed on the system, if available" YES)
find_package(GTest)
if (NOT GTEST_FOUND OR NOT USE_SYSTEM_GTEST)
    #Google test framework
    ExternalProject_Add(ext-gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG "release-1.8.1"
        CMAKE_ARGS -DBUILD_GMOCK=NO
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        )

    add_library(gtest IMPORTED STATIC GLOBAL)
    add_dependencies(gtest ext-gtest)
    add_library(gtest_main IMPORTED STATIC GLOBAL)
    add_dependencies(gtest_main ext-gtest)

    ExternalProject_Get_Property(ext-gtest source_dir binary_dir)

    find_package(Threads)
    set_target_properties(gtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googletest/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

    set_target_properties(gtest_main PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googletest/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

    set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include)
    set(GTEST_LIBRARIES gtest)
    set(GTEST_MAIN_LIBRARIES gtest_main)
    set(GTEST_BOTH_LIBRARIES gtest_main gtest)
else ()
    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED)
endif ()

find_package(OpenCL)

add_subdirectory(lib)

if(${OpenCL_FOUND})
    add_compile_definitions(NAIVE)
    add_subdirectory(gpu)
    include_directories(${OpenCL_INCLUDE_DIRS})
    link_directories(${OpenCL_LIBRARY})

    add_executable(OpenCLTest maingpu.cpp)
    target_include_directories (OpenCLTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries (OpenCLTest ${OpenCL_LIBRARY})
    target_link_libraries (OpenCLTest gpulib)
endif()

add_executable(simulate main.cpp)
target_link_libraries(simulate libcellularautomata)
