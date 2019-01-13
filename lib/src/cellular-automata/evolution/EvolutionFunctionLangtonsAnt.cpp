#include "cellular-automata/evolution/EvolutionFunctionLangtonsAnt.hpp"

using namespace std;

namespace {
constexpr CellularAutomata::Index index_N = CellularAutomata::Index::make(-0, -1);
constexpr CellularAutomata::Index index_E = CellularAutomata::Index::make(+1, -0);
constexpr CellularAutomata::Index index_S = CellularAutomata::Index::make(+0, +1);
constexpr CellularAutomata::Index index_W = CellularAutomata::Index::make(-1, +0);
}

namespace CellularAutomata {

void EvolutionFunctionLangtonsAnt::operator()(shared_ptr<ElementMapper> mapper) {
    m_mapper = mapper.get();
}

void EvolutionFunctionLangtonsAnt::operator()(const ArrayMapper & prev,
                                              ArrayMapper & next,
                                              const Index & index) const {

    // White cell: [0] == false
    // Black cell: [0] == true
    // Direction:  [1] = {
    constexpr int8_t dir_up = 1;
    constexpr int8_t dir_right = 2;
    constexpr int8_t dir_down = 3;
    constexpr int8_t dir_left = 4;
    // White cell: turn right, flip, and move forward
    // Black cell: turn left,  flip, and move forward

    int8_t ant_result = 0;

    {
        Index neighbour = index - index_N;
        if (prev.exists(neighbour)) { // Up neighbour
            bool color = m_mapper->map<bool>(prev(neighbour), 0);
            int8_t ant = m_mapper->map<int8_t>(prev(neighbour), 1);

            if (color ? ant == dir_right : ant == dir_left) {
                if (ant_result > 0) {
                    ant_result = -1;
                } else {
                    ant_result = dir_down;
                }
            }
        }
    }
    if (ant_result != -1) {
        Index neighbour = index - index_E;
        if (prev.exists(neighbour)) { // Right neighbour
            bool color = m_mapper->map<bool>(prev(neighbour), 0);
            int8_t ant = m_mapper->map<int8_t>(prev(neighbour), 1);

            if (color ? ant == dir_down : ant == dir_up) {
                if (ant_result > 0) {
                    ant_result = -1;
                } else {
                    ant_result = dir_left;
                }
            }
        }
    }
    if (ant_result != -1) {
        Index neighbour = index - index_S;
        if (prev.exists(neighbour)) { // Down neighbour
            bool color = m_mapper->map<bool>(prev(neighbour), 0);
            int8_t ant = m_mapper->map<int8_t>(prev(neighbour), 1);

            if (color ? ant == dir_left : ant == dir_right) {
                if (ant_result > 0) {
                    ant_result = -1;
                } else {
                    ant_result = dir_up;
                }
            }
        }
    }
    if (ant_result != -1) {
        Index neighbour = index - index_W;
        if (prev.exists(neighbour)) { // Left neighbour
            bool color = m_mapper->map<bool>(prev(neighbour), 0);
            int8_t ant = m_mapper->map<int8_t>(prev(neighbour), 1);

            if (color ? ant == dir_up : ant == dir_down) {
                if (ant_result > 0) {
                    ant_result = -1;
                } else {
                    ant_result = dir_right;
                }
            }
        }
    }

    m_mapper->map<int8_t>(next(index), 1) = ant_result == -1 ? 0 : ant_result;

    if (m_mapper->map<int8_t>(prev(index), 1) > 0) {
        m_mapper->map<bool>(next(index), 0) = !m_mapper->map<bool>(prev(index), 0);
    }
}

}
