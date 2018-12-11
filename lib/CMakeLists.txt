set(SOURCES
    src/cellular-automata/evolution/EvolutionFunctionLife.cpp
    src/cellular-automata/evolution/EvolutionFunctionRule.cpp
    src/cellular-automata/storage/ArrayMapper1D.cpp
    src/cellular-automata/storage/ArrayMapper2D.cpp
    src/cellular-automata/storage/ElementMapper.cpp
    src/cellular-automata/storage/ElementMapperImpl.cpp
    src/cellular-automata/storage/FlexibleArray.cpp
    src/cellular-automata/game-of-life.cpp
    src/cellular-automata/Simulator.cpp
    )

add_library(libcellularautomata ${SOURCES})
target_include_directories(libcellularautomata PUBLIC include)

add_subdirectory(test)
