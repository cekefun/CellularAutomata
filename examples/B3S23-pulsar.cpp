#include "cellular-automata/game-of-life.hpp"

#include <iostream>

using namespace CellularAutomata;

int main() {
    GameOfLife pulsar(17, 17);

    /**
     * _________________
     * _________________
     * ____ooo___ooo____
     * _________________
     * __o____o_o____o__
     * __o____o_o____o__
     * __o____o_o____o__
     * ____ooo___ooo____
     * _________________
     * ____ooo___ooo____
     * __o____o_o____o__
     * __o____o_o____o__
     * __o____o_o____o__
     * _________________
     * ____ooo___ooo____
     * _________________
     * _________________
     */
    // Top left quadrant
    pulsar(2, 4) = true;
    pulsar(2, 5) = true;
    pulsar(2, 6) = true;
    pulsar(4, 2) = true;
    pulsar(5, 2) = true;
    pulsar(6, 2) = true;
    pulsar(7, 4) = true;
    pulsar(7, 5) = true;
    pulsar(7, 6) = true;
    pulsar(4, 7) = true;
    pulsar(5, 7) = true;
    pulsar(6, 7) = true;
    // Top right quadrant
    pulsar(2, 10) = true;
    pulsar(2, 11) = true;
    pulsar(2, 12) = true;
    pulsar(4, 14) = true;
    pulsar(5, 14) = true;
    pulsar(6, 14) = true;
    pulsar(7, 10) = true;
    pulsar(7, 11) = true;
    pulsar(7, 12) = true;
    pulsar(4, 9) = true;
    pulsar(5, 9) = true;
    pulsar(6, 9) = true;
    // Bottom left quadrant
    pulsar(14, 4) = true;
    pulsar(14, 5) = true;
    pulsar(14, 6) = true;
    pulsar(10, 2) = true;
    pulsar(11, 2) = true;
    pulsar(12, 2) = true;
    pulsar(9, 4) = true;
    pulsar(9, 5) = true;
    pulsar(9, 6) = true;
    pulsar(10, 7) = true;
    pulsar(11, 7) = true;
    pulsar(12, 7) = true;
    // Bottom right quadrant
    pulsar(14, 10) = true;
    pulsar(14, 11) = true;
    pulsar(14, 12) = true;
    pulsar(10, 14) = true;
    pulsar(11, 14) = true;
    pulsar(12, 14) = true;
    pulsar(9, 10) = true;
    pulsar(9, 11) = true;
    pulsar(9, 12) = true;
    pulsar(10, 9) = true;
    pulsar(11, 9) = true;
    pulsar(12, 9) = true;

    std::cout << "Initial grid:" << std::endl;
    std::cout << pulsar.toString() << std::endl;

    for (unsigned int i = 0; i < 6; ++i) {
        std::cout << "Running timestep " << i << std::endl;

        pulsar.timeStep();

        std::cout << "Grid:" << std::endl;
        std::cout << pulsar.toString() << std::endl;
    }

    return 0;
}
