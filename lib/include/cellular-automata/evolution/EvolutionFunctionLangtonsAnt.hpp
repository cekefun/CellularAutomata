#pragma once

#include "cellular-automata/evolution/EvolutionFunction.hpp"

#include <bitset>

namespace CellularAutomata {

class EvolutionFunctionLangtonsAnt : public EvolutionFunction {
public:
    EvolutionFunctionLangtonsAnt() = default;

    void operator()(std::shared_ptr<ElementMapper> mapper) override;

    void operator()(const ArrayMapper & prev, ArrayMapper & next, const Index & index) const override;

private:
    std::shared_ptr<ElementMapper> m_mapper {};
};

}
