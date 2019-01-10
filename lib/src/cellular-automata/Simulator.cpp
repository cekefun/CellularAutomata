#include "cellular-automata/Simulator.hpp"

#include "cellular-automata/profiler.hpp"

#include <cstdio>
#include <map>
#include <sstream>

#include <omp.h>

using namespace std;

namespace CellularAutomata {

Simulator::Simulator(shared_ptr<ArrayMapper> data,
                     shared_ptr<ElementMapper> mapper,
                     shared_ptr<EvolutionFunction> evolve)
    : m_data(move(data)), m_mapper(move(mapper)), m_evolve(move(evolve)), m_oldStates() {
    (*m_evolve)(m_mapper);
}

void Simulator::step() {
    PROFILER_BLOCK("simulator:step", omp_get_thread_num());

    shared_ptr<ArrayMapper> copy(move(m_data->clone()));

    const vector<Index> & indexes = m_data->indexes();

#pragma omp parallel
    {
        size_t size = indexes.size();

#pragma omp for
        for (size_t i = 0; i < size; ++i) {
            PROFILER_BLOCK("simulator:step-bit", omp_get_thread_num());

            const Index & index = indexes[i];

            (*m_evolve)(*m_data, *copy, index);
        }
    }

    m_oldStates.emplace_back(m_data);

    m_data = std::move(copy);
}

void Simulator::printResult() {
    // Temporary function that implements printing of life-like cells (dead or alive) for 1 dimensional arrays
    // In the very near future, you would plug in another object that can output to any (within reason) format

    unsigned int i = 0;

    for (const auto & state : m_oldStates) {
        std::printf("State %3d: ", i++);

        Index::Dimensionality dimensionality = state->getDimensionality();

        if (dimensionality == Index::Dimensionality::ONE) {
            for (const auto & index : state->indexes()) {
                std::printf("%s", m_mapper->map<bool>((*state)(index)) ? "o" : ".");
            }
        } else if (dimensionality == Index::Dimensionality::TWO) {
            std::map<int64_t, stringstream> lines;
            for (const auto & index : state->indexes()) {
                lines[index.y] << (m_mapper->map<bool>((*state)(index)) ? "o" : ".");
            }

            for (const auto & line : lines) {
                std::printf("\n%3ld: %s", line.first, line.second.str().c_str());
            }
        }

        std::printf("\n");
    }

    std::printf("State %3d: ", i);

    Index::Dimensionality dimensionality = m_data->getDimensionality();

    if (dimensionality == Index::Dimensionality::ONE) {
        for (const auto & index : m_data->indexes()) {
            std::printf("%s", m_mapper->map<bool>((*m_data)(index)) ? "o" : ".");
        }
    } else if (dimensionality == Index::Dimensionality::TWO) {
        std::map<int64_t, stringstream> lines;
        for (const auto & index : m_data->indexes()) {
            lines[index.y] << (m_mapper->map<bool>((*m_data)(index)) ? "o" : ".");
        }

        for (const auto & line : lines) {
            std::printf("\n%3ld: %s", line.first, line.second.str().c_str());
        }
    }

    std::printf("\n");
}

}
