cmake_minimum_required(VERSION 3.8)
project(CellularAtuomata)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest)
if (NOT GTEST_FOUND)
    #Google test framework
    ExternalProject_Add(ext-gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        CMAKE_ARGS -DBUILD_GMOCK=NO -DBUILD_GTEST=YES
        INSTALL_COMMAND ""
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
    include_directories(${source_dir}/googletest/include)
    set(GTEST_LIBRARIES gtest)
    set(GTEST_BOTH_LIBRARIES gtest_main gtest)
else()
    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED)
    include_directories(GTEST_INCLUDE_DIRS)
    set(GTEST_BOTH_LIBRARIES gtest_main gtest ${CMAKE_THREAD_LIBS_INIT})
endif()

find_package(OpenCL)

add_subdirectory(lib)

#if(${OpenCL_FOUND})
#    add_subdirectory(gpu)
#endif()

add_executable(simulate main.cpp)
target_link_libraries(simulate libcellularautomata)
