cmake_minimum_required(VERSION 3.8)
project(CellularAtuomata)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")

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

find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

find_package(Boost)
find_package(OpenCL)

add_subdirectory(lib)

if (${OpenCL_FOUND})
    # add_subdirectory(gpu)

    # add_executable(OpenCLTest maingpu.cpp)
    # target_include_directories(OpenCLTest PRIVATE ${OpenCL_INCLUDE_DIRS})
    # target_link_libraries(OpenCLTest ${OpenCL_LIBRARIES})
    # target_link_libraries(OpenCLTest gpulib)
endif ()

add_executable(simulate main.cpp)
target_link_libraries(simulate libcellularautomata)

include(CMakeReport.cmake)
