#include "cellular-automata/evolution/EvolutionFunctionRule.hpp"

using namespace std;

namespace CellularAutomata {

EvolutionFunctionRule::EvolutionFunctionRule(uint8_t rule)
    : m_rule(rule) {}

void EvolutionFunctionRule::operator()(shared_ptr<CellularAutomata::ElementMapper> mapper) {
    m_mapper = mapper;
}

void EvolutionFunctionRule::operator()(const CellularAutomata::ArrayMapper & prev,
                                       CellularAutomata::ArrayMapper & next,
                                       const CellularAutomata::Index & index) const {
    bool l = prev.exists(index - c_index_one) ? m_mapper->map<bool>(prev(index - c_index_one)) : false;
    bool c = m_mapper->map<bool>(prev(index));
    bool r = prev.exists(index + c_index_one) ? m_mapper->map<bool>(prev(index + c_index_one)) : false;

    auto bit = static_cast<uint8_t>((l ? 0b100 : 0) | (c ? 0b10 : 0) | (r ? 0b1 : 0));

    // m_mapper->map<bool>(next(index)) = m_rule & (1 << bit);
    if (m_rule & (1 << bit)) {
        if (!c) {
            m_mapper->map<bool>(next(index)) = true;
        }
    } else {
        if (c) {
            m_mapper->map<bool>(next(index)) = false;
        }
    }
}

}
