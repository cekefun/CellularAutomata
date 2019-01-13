#pragma once

#include "cellular-automata/evolution/EvolutionFunction.hpp"

#include <bitset>

namespace CellularAutomata {

class EvolutionFunctionLangtonsAnt : public EvolutionFunction {
public:
    EvolutionFunctionLangtonsAnt() = default;

    EvolutionFunctionLangtonsAnt(const EvolutionFunctionLangtonsAnt &) = delete;

    EvolutionFunctionLangtonsAnt(EvolutionFunctionLangtonsAnt &&) = delete;

    EvolutionFunctionLangtonsAnt & operator=(const EvolutionFunctionLangtonsAnt &) = delete;

    EvolutionFunctionLangtonsAnt & operator=(EvolutionFunctionLangtonsAnt &&) = delete;

    void operator()(std::shared_ptr<ElementMapper> mapper) override;

    void operator()(const ArrayMapper & prev, ArrayMapper & next, const Index & index) const override;

private:
    ElementMapper * m_mapper = nullptr;
};

}
