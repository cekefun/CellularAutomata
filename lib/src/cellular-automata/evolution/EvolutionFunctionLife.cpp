#include <utility>

#include <utility>

#include "cellular-automata/evolution/EvolutionFunctionLife.hpp"

using namespace std;

namespace CellularAutomata {

EvolutionFunctionLife::EvolutionFunctionLife(bitset<8> born, bitset<8> survive)
    : m_born(born), m_survive(survive) {}

void EvolutionFunctionLife::operator()(shared_ptr<CellularAutomata::ElementMapper> mapper) {
    m_mapper = mapper;
}

void EvolutionFunctionLife::operator()(const CellularAutomata::ArrayMapper & prev,
                                       CellularAutomata::ArrayMapper & next,
                                       const CellularAutomata::Index & index) const {
    uint8_t numNeighbours = 0;

    bool alive = m_mapper->map<bool>(prev(index));

    if (prev.exists(index - Index { -1, -1 }) && m_mapper->map<bool>(prev(index - Index { -1, -1 }))) ++numNeighbours;
    if (prev.exists(index - Index { -0, -1 }) && m_mapper->map<bool>(prev(index - Index { -0, -1 }))) ++numNeighbours;
    if (prev.exists(index - Index { +1, -1 }) && m_mapper->map<bool>(prev(index - Index { +1, -1 }))) ++numNeighbours;
    if (prev.exists(index - Index { +1, -0 }) && m_mapper->map<bool>(prev(index - Index { +1, -0 }))) ++numNeighbours;
    if (prev.exists(index - Index { +1, +1 }) && m_mapper->map<bool>(prev(index - Index { +1, +1 }))) ++numNeighbours;
    if (prev.exists(index - Index { +0, +1 }) && m_mapper->map<bool>(prev(index - Index { +0, +1 }))) ++numNeighbours;
    if (prev.exists(index - Index { -1, +1 }) && m_mapper->map<bool>(prev(index - Index { -1, +1 }))) ++numNeighbours;
    if (prev.exists(index - Index { -1, +0 }) && m_mapper->map<bool>(prev(index - Index { -1, +0 }))) ++numNeighbours;

    // m_mapper->map<bool>(next(index)) = m_rule & (1 << bit);
    if (alive && !m_survive[numNeighbours]) {
        m_mapper->map<bool>(next(index)) = false;
    } else if (!alive && m_born[numNeighbours]) {
        m_mapper->map<bool>(next(index)) = true;
    }
}

}
