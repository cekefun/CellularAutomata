#include "cellular-automata/Simulator.hpp"

#include <stdio.h>

using namespace std;

namespace CellularAutomata {

Simulator::Simulator(shared_ptr<ArrayMapper> data,
                     shared_ptr<ElementMapper> mapper,
                     shared_ptr<EvolutionFunction> evolve)
    : m_data(move(data)), m_mapper(move(mapper)), m_evolve(move(evolve)), m_oldStates() {
    (*m_evolve)(m_mapper);
}

void Simulator::step() {
    shared_ptr<ArrayMapper> copy = m_data->clone();

    const vector<Index> & indexes = m_data->indexes();

    for (const auto & index : indexes) {
        (*m_evolve)(*m_data, *copy, index);
    }

    m_oldStates.emplace_back(m_data);

    m_data = std::move(copy);
}

void Simulator::printResult() {
    // Temporary function that implements printing of life-like cells (dead or alive) for 1 dimensional arrays
    // In the future, you would plug in another object that can output to any (within reason) format

    unsigned int i = 0;

    for (const auto & state : m_oldStates) {
        std::printf("State %3d: ", i++);

        for (const auto & index : state->indexes()) {
            std::printf("%s", m_mapper->map<bool>((*state)(index)) ? "o" : ".");
        }

        std::printf("\n");
    }

    std::printf("State %3d: ", i);

    for (const auto & index : m_data->indexes()) {
        std::printf("%s", m_mapper->map<bool>((*m_data)(index)) ? "o" : ".");
    }

    std::printf("\n");
}

}
