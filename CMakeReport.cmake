message(STATUS " ")

# Environment
message(STATUS "----- CMAKE_SYSTEM                      : ${CMAKE_SYSTEM}")
message(STATUS "----- CMAKE_SYSTEM_VERSION              : ${CMAKE_SYSTEM_VERSION}")
message(STATUS "----- CMAKE_SYSTEM_PROCESSOR            : ${CMAKE_SYSTEM_PROCESSOR}")
include(ProcessorCount)
ProcessorCount(PROCCOUNT)
message(STATUS "----- PROCESSOR_COUNT                   : ${PROCCOUNT}")
message(STATUS "----- CMAKE_VERSION                     : ${CMAKE_VERSION}")
message(STATUS "----- ENVIRONMENT PATH                  : $ENV{PATH}")

message(STATUS " ")

# Build
message(STATUS "----- CMAKE_BUILD_TYPE                  : ${CMAKE_BUILD_TYPE}")
message(STATUS "----- CMAKE_BINARY_DIR                  : ${CMAKE_BINARY_DIR}")
message(STATUS "----- CMAKE_INSTALL_PREFIX              : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "----- CMAKE_CXX_COMPILER                : ${CMAKE_CXX_COMPILER}")
message(STATUS "----- CMAKE_CXX_COMPILER_ID             : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "----- CMAKE_CXX_COMPILER_VERSION        : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "----- CMAKE_CXX_FLAGS                   : ${CMAKE_CXX_FLAGS}")
if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease$")
    message(STATUS "----- CMAKE_CXX_FLAGS_RELEASE           : ${CMAKE_CXX_FLAGS_RELEASE}")
endif ()
if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug$")
    message(STATUS "----- CMAKE_CXX_FLAGS_DEBUG             : ${CMAKE_CXX_FLAGS_DEBUG}")
endif ()

message(STATUS " ")

# Gtest
message(STATUS "----- OpenMP_C_FLAGS                    : ${OpenMP_C_FLAGS}")
message(STATUS "----- OpenMP_CXX_FLAGS                  : ${OpenMP_CXX_FLAGS}")
message(STATUS "----- CMAKE_EXE_LINKER_FLAGS            : ${CMAKE_EXE_LINKER_FLAGS}")

message(STATUS " ")

# OpenMP
message(STATUS "----- GTEST_INCLUDE_DIRS                : ${GTEST_INCLUDE_DIRS}")
message(STATUS "----- GTEST_BOTH_LIBRARIES              : ${GTEST_BOTH_LIBRARIES}")

message(STATUS " ")

# OpenCL
message(STATUS "----- OpenCL_FOUND                      : ${OpenCL_FOUND}")
if (${OpenCL_FOUND})
    message(STATUS "----- OpenCL_INCLUDE_DIRS               : ${OpenCL_INCLUDE_DIRS}")
    message(STATUS "----- OpenCL_LIBRARIES                  : ${OpenCL_LIBRARIES}")
endif ()

message(STATUS " ")

# Boost
message(STATUS "----- Boost_FOUND                       : ${Boost_FOUND}")
if (${Boost_FOUND})
    message(STATUS "----- Boost_INCLUDE_DIRS                : ${Boost_INCLUDE_DIRS}")
    message(STATUS "----- Boost_LIBRARIES                   : ${Boost_LIBRARIES}")
endif ()

message(STATUS " ")

function(GetTargetPropertyClean targetName property)
    get_target_property(TEMPORARY_PROPERTY ${targetName} ${property})

    if (TEMPORARY_PROPERTY STREQUAL "TEMPORARY_PROPERTY-NOTFOUND")
        set(GetTargetPropertyClean_RESULT "" PARENT_SCOPE)
    else ()
        set(GetTargetPropertyClean_RESULT ${TEMPORARY_PROPERTY} PARENT_SCOPE)
    endif ()
endfunction()

function(ReportTarget targetName)
    message(STATUS "----- Target: ${targetName}")

    GetTargetPropertyClean(${targetName} COMPILE_DEFINITIONS)
    message(STATUS "----- COMPILE_DEFINITIONS               : ${GetTargetPropertyClean_RESULT}")

    GetTargetPropertyClean(${targetName} INTERFACE_COMPILE_DEFINITIONS)
    message(STATUS "----- INTERFACE_COMPILE_DEFINITIONS     : ${GetTargetPropertyClean_RESULT}")

    GetTargetPropertyClean(${targetName} COMPILE_OPTIONS)
    message(STATUS "----- COMPILE_OPTIONS                   : ${GetTargetPropertyClean_RESULT}")

    GetTargetPropertyClean(${targetName} INTERFACE_COMPILE_OPTIONS)
    message(STATUS "----- INTERFACE_COMPILE_OPTIONS         : ${GetTargetPropertyClean_RESULT}")

    GetTargetPropertyClean(${targetName} INCLUDE_DIRECTORIES)
    message(STATUS "----- INCLUDE_DIRECTORIES               : ${GetTargetPropertyClean_RESULT}")

    GetTargetPropertyClean(${targetName} INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "----- INTERFACE_INCLUDE_DIRECTORIES     : ${GetTargetPropertyClean_RESULT}")

    GetTargetPropertyClean(${targetName} LINK_FLAGS)
    message(STATUS "----- LINK_FLAGS                        : ${GetTargetPropertyClean_RESULT}")

    GetTargetPropertyClean(${targetName} LINK_OPTIONS)
    message(STATUS "----- LINK_OPTIONS                      : ${GetTargetPropertyClean_RESULT}")

    GetTargetPropertyClean(${targetName} INTERFACE_LINK_OPTIONS)
    message(STATUS "----- INTERFACE_LINK_OPTIONS            : ${GetTargetPropertyClean_RESULT}")

    message(STATUS " ")
endfunction()

# Target: libcellularautomata
if (TARGET libcellularautomata)
    ReportTarget(libcellularautomata)
endif ()

# Target: libcellularautomata-test
if (TARGET libcellularautomata-test)
    ReportTarget(libcellularautomata-test)
endif ()

# Target: simulate
if (TARGET simulate)
    ReportTarget(simulate)
endif ()

# Target: gpulib
if (TARGET gpulib)
    ReportTarget(gpulib)
endif ()

# Target: OpenCLTest
if (TARGET OpenCLTest)
    ReportTarget(OpenCLTest)
endif ()
