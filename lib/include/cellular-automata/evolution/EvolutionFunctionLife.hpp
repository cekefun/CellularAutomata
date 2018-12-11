#pragma once

#include "cellular-automata/evolution/EvolutionFunction.hpp"

#include <bitset>

namespace CellularAutomata {

class EvolutionFunctionLife : public EvolutionFunction {
public:
    EvolutionFunctionLife(std::bitset<8> born, std::bitset<8> survive);

    void operator()(std::shared_ptr<ElementMapper> mapper) override;

    void operator()(const ArrayMapper & prev, ArrayMapper & next, const Index & index) const override;

private:
    std::bitset<8> m_born;
    std::bitset<8> m_survive;
    std::shared_ptr<ElementMapper> m_mapper;
};

}
