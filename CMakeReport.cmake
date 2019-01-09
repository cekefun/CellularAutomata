message(STATUS " ")

# Environment
message(STATUS "----- CMAKE_SYSTEM                : ${CMAKE_SYSTEM}")
message(STATUS "----- CMAKE_SYSTEM_VERSION        : ${CMAKE_SYSTEM_VERSION}")
message(STATUS "----- CMAKE_SYSTEM_PROCESSOR      : ${CMAKE_SYSTEM_PROCESSOR}")
include(ProcessorCount)
ProcessorCount(PROCCOUNT)
message(STATUS "----- PROCESSOR_COUNT             : ${PROCCOUNT}")
message(STATUS "----- CMAKE_VERSION               : ${CMAKE_VERSION}")
message(STATUS "----- ENVIRONMENT PATH            : $ENV{PATH}")

message(STATUS " ")

# Build
message(STATUS "----- CMAKE_BUILD_TYPE            : ${CMAKE_BUILD_TYPE}")
message(STATUS "----- CMAKE_BINARY_DIR            : ${CMAKE_BINARY_DIR}")
message(STATUS "----- CMAKE_INSTALL_PREFIX        : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "----- CMAKE_CXX_COMPILER          : ${CMAKE_CXX_COMPILER}")
message(STATUS "----- CMAKE_CXX_COMPILER_ID       : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "----- CMAKE_CXX_COMPILER_VERSION  : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "----- CMAKE_CXX_FLAGS             : ${CMAKE_CXX_FLAGS}")
if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease$")
    message(STATUS "----- CMAKE_CXX_FLAGS_RELEASE     : ${CMAKE_CXX_FLAGS_RELEASE}")
endif ()
if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug$")
    message(STATUS "----- CMAKE_CXX_FLAGS_DEBUG       : ${CMAKE_CXX_FLAGS_DEBUG}")
endif ()

message(STATUS " ")

# Gtest
message(STATUS "----- OpenMP_C_FLAGS              : ${OpenMP_C_FLAGS}")
message(STATUS "----- OpenMP_CXX_FLAGS            : ${OpenMP_CXX_FLAGS}")
message(STATUS "----- CMAKE_EXE_LINKER_FLAGS      : ${CMAKE_EXE_LINKER_FLAGS}")

message(STATUS " ")

# OpenMP
message(STATUS "----- GTEST_INCLUDE_DIRS          : ${GTEST_INCLUDE_DIRS}")
message(STATUS "----- GTEST_BOTH_LIBRARIES        : ${GTEST_BOTH_LIBRARIES}")

message(STATUS " ")
