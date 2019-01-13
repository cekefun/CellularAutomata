#include "cellular-automata/evolution/EvolutionFunctionLife.hpp"

using namespace std;

namespace {
constexpr CellularAutomata::Index index_NW = CellularAutomata::Index::make(-1, -1);
constexpr CellularAutomata::Index index_N_ = CellularAutomata::Index::make(-0, -1);
constexpr CellularAutomata::Index index_NE = CellularAutomata::Index::make(+1, -1);
constexpr CellularAutomata::Index index__E = CellularAutomata::Index::make(+1, -0);
constexpr CellularAutomata::Index index_SE = CellularAutomata::Index::make(+1, +1);
constexpr CellularAutomata::Index index_S_ = CellularAutomata::Index::make(+0, +1);
constexpr CellularAutomata::Index index_SW = CellularAutomata::Index::make(-1, +1);
constexpr CellularAutomata::Index index__W = CellularAutomata::Index::make(-1, +0);
}

namespace CellularAutomata {

EvolutionFunctionLife::EvolutionFunctionLife(bitset<8> born, bitset<8> survive)
    : m_born(born), m_survive(survive) {}

void EvolutionFunctionLife::operator()(shared_ptr<ElementMapper> mapper) {
    m_mapper = mapper.get();
}

void EvolutionFunctionLife::operator()(const ArrayMapper & prev,
                                       ArrayMapper & next,
                                       const Index & index) const {

    uint8_t numNeighbours = 0;

    bool alive = m_mapper->map<bool>(prev(index));

    if (prev.exists(index - index_NW) && m_mapper->map<bool>(prev(index - index_NW))) ++numNeighbours;
    if (prev.exists(index - index_N_) && m_mapper->map<bool>(prev(index - index_N_))) ++numNeighbours;
    if (prev.exists(index - index_NE) && m_mapper->map<bool>(prev(index - index_NE))) ++numNeighbours;
    if (prev.exists(index - index__E) && m_mapper->map<bool>(prev(index - index__E))) ++numNeighbours;
    if (prev.exists(index - index_SE) && m_mapper->map<bool>(prev(index - index_SE))) ++numNeighbours;
    if (prev.exists(index - index_S_) && m_mapper->map<bool>(prev(index - index_S_))) ++numNeighbours;
    if (prev.exists(index - index_SW) && m_mapper->map<bool>(prev(index - index_SW))) ++numNeighbours;
    if (prev.exists(index - index__W) && m_mapper->map<bool>(prev(index - index__W))) ++numNeighbours;

    // m_mapper->map<bool>(next(index)) = m_rule & (1 << bit);
    if (alive && !m_survive[numNeighbours]) {
        m_mapper->map<bool>(next(index)) = false;
    } else if (!alive && m_born[numNeighbours]) {
        m_mapper->map<bool>(next(index)) = true;
    }
}

}
