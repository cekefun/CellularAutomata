#include "cellular-automata/game-of-life.hpp"

#include <iostream>

using namespace CellularAutomata;

int main() {
    GameOfLife blinker(5, 5);

    /**
     * _____
     * __o__
     * __o__
     * __o__
     * _____
     */
    blinker(1, 2) = true;
    blinker(2, 2) = true;
    blinker(3, 2) = true;

    std::cout << "Initial grid:" << std::endl;
    std::cout << blinker.toString() << std::endl;

    for (unsigned int i = 0; i < 5; ++i) {
        std::cout << "Running timestep " << i << std::endl;

        blinker.timeStep();

        std::cout << "Grid:" << std::endl;
        std::cout << blinker.toString() << std::endl;
    }

    return 0;
}
