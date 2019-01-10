#include "cellular-automata/evolution/EvolutionFunctionRule.hpp"

#include "cellular-automata/profiler.hpp"
#include "omp-helper.hpp"

using namespace std;

namespace CellularAutomata {

EvolutionFunctionRule::EvolutionFunctionRule(uint8_t rule)
    : m_rule(rule) {}

void EvolutionFunctionRule::operator()(shared_ptr<ElementMapper> mapper) {
    m_mapper = mapper;
}

void EvolutionFunctionRule::operator()(const ArrayMapper & prev,
                                       ArrayMapper & next,
                                       const Index & index) const {
    PROFILER_BLOCK("evolution:rule", omp::getThreadNumber());

    bool l = prev.exists(index - c_index_one) ? m_mapper->map<bool>(prev(index - c_index_one)) : false;
    bool c = m_mapper->map<bool>(prev(index));
    bool r = prev.exists(index + c_index_one) ? m_mapper->map<bool>(prev(index + c_index_one)) : false;

    auto bit = static_cast<uint8_t>((l ? 4u : 0u) | (c ? 2u : 0u) | (r ? 1u : 0u));

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
