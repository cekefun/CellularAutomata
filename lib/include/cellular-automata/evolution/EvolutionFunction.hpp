#pragma once

#include "cellular-automata/storage/ArrayMapper.hpp"
#include "cellular-automata/storage/ElementMapper.hpp"

namespace CellularAutomata {

class EvolutionFunction {
public:
    EvolutionFunction() = default;

    EvolutionFunction(const EvolutionFunction &) = delete;

    EvolutionFunction(EvolutionFunction &&) = delete;

    EvolutionFunction & operator=(const EvolutionFunction &) = delete;

    EvolutionFunction & operator=(EvolutionFunction &&) = delete;

    virtual ~EvolutionFunction() = default;

    virtual void operator()(std::shared_ptr<ElementMapper> mapper) = 0;

    virtual void operator()(const ArrayMapper & prev, ArrayMapper & next, const Index & index) const = 0;
};

}
