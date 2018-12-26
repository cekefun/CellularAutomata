#pragma once

#include "cellular-automata/evolution/EvolutionFunction.hpp"

namespace CellularAutomata {

class EvolutionFunctionRule : public EvolutionFunction {
public:
    explicit EvolutionFunctionRule(std::uint8_t rule);

    void operator()(std::shared_ptr<ElementMapper> mapper) override;

    void operator()(const ArrayMapper & prev, ArrayMapper & next, const Index & index) const override;

private:
    std::uint8_t m_rule;
    std::shared_ptr<ElementMapper> m_mapper;

    const Index c_index_one { 1 };
};

}
