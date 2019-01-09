set(SOURCES
    test_Empty.cpp
    )

add_executable(libcellularautomata-test ${SOURCES})

target_include_directories(libcellularautomata-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(libcellularautomata-test libcellularautomata ${GTEST_BOTH_LIBRARIES})

gtest_add_tests(TARGET libcellularautomata-test)
