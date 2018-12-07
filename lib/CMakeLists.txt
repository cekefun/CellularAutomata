set(SOURCES
    src/cellular-automata/game-of-life.cpp
    src/cellular-automata/index-space.cpp
    src/cellular-automata/FlexibleArray.cpp
    src/cellular-automata/FlexibleArrayImpl.cpp
    )

add_library(libcellularautomata ${SOURCES})
target_include_directories(libcellularautomata PUBLIC include)

add_subdirectory(test)
