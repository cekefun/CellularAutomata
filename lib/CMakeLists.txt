set(SOURCES
    src/cellular-automata/game-of-life.cpp
    )

add_library(libcellularautomata ${SOURCES})
target_include_directories(libcellularautomata PUBLIC include)

add_subdirectory(test)
