#pragma once

#include "cellular-automata/evolution/EvolutionFunction.hpp"
#include "cellular-automata/storage/ArrayMapper.hpp"
#include "cellular-automata/storage/ElementMapper.hpp"

#include <list>

namespace CellularAutomata {
class Simulator {
public:
    Simulator(std::shared_ptr<ArrayMapper> data, std::shared_ptr<ElementMapper> mapper, std::shared_ptr<EvolutionFunction> evolve);

    void step();

    // TEMPORARY FUNCTION
    [[deprecated]]
    void printResult();

private:
    std::shared_ptr<ArrayMapper> m_data;
    std::shared_ptr<ElementMapper> m_mapper;
    std::shared_ptr<EvolutionFunction> m_evolve;

    std::list<std::shared_ptr<ArrayMapper>> m_oldStates;
};
}
