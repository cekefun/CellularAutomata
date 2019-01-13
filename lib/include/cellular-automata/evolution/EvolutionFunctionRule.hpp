#pragma once

#include "cellular-automata/evolution/EvolutionFunction.hpp"

namespace CellularAutomata {

class EvolutionFunctionRule : public EvolutionFunction {
public:
    explicit EvolutionFunctionRule(std::uint8_t rule);

    EvolutionFunctionRule(const EvolutionFunctionRule &) = delete;

    EvolutionFunctionRule(EvolutionFunctionRule &&) = delete;

    EvolutionFunctionRule & operator=(const EvolutionFunctionRule &) = delete;

    EvolutionFunctionRule & operator=(EvolutionFunctionRule &&) = delete;

    void operator()(std::shared_ptr<ElementMapper> mapper) override;

    void operator()(const ArrayMapper & prev, ArrayMapper & next, const Index & index) const override;

private:
    std::uint8_t m_rule;
    ElementMapper * m_mapper = nullptr;
};

}
