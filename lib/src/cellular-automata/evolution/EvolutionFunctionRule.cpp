#include "cellular-automata/evolution/EvolutionFunctionRule.hpp"

using namespace std;

namespace {
constexpr CellularAutomata::Index index_one = CellularAutomata::Index::make(1);
}

namespace CellularAutomata {

EvolutionFunctionRule::EvolutionFunctionRule(uint8_t rule)
    : m_rule(rule) {}

void EvolutionFunctionRule::operator()(shared_ptr<ElementMapper> mapper) {
    m_mapper = mapper.get();
}

void EvolutionFunctionRule::operator()(const ArrayMapper & prev,
                                       ArrayMapper & next,
                                       const Index & index) const {

    bool l = prev.exists(index - index_one) ? m_mapper->map<bool>(prev(index - index_one)) : false;
    bool c = m_mapper->map<bool>(prev(index));
    bool r = prev.exists(index + index_one) ? m_mapper->map<bool>(prev(index + index_one)) : false;

    auto bit = static_cast<uint8_t>((l << 2) | (c << 1) | (r << 0));

    // m_mapper->map<bool>(next(index)) = m_rule & (1 << bit);
    if (m_rule & (1u << bit)) {
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
