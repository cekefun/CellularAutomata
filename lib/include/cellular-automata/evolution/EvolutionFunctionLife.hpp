#pragma once

#include "cellular-automata/evolution/EvolutionFunction.hpp"

#include <bitset>

namespace CellularAutomata {

class EvolutionFunctionLife : public EvolutionFunction {
public:
    EvolutionFunctionLife(std::bitset<8> born, std::bitset<8> survive);

    EvolutionFunctionLife(const EvolutionFunctionLife &) = delete;

    EvolutionFunctionLife(EvolutionFunctionLife &&) = delete;

    EvolutionFunctionLife & operator=(const EvolutionFunctionLife &) = delete;

    EvolutionFunctionLife & operator=(EvolutionFunctionLife &&) = delete;

    void operator()(std::shared_ptr<ElementMapper> mapper) override;

    void operator()(const ArrayMapper & prev, ArrayMapper & next, const Index & index) const override;

private:
    std::bitset<8> m_born;
    std::bitset<8> m_survive;
    ElementMapper * m_mapper = nullptr;
};

}
