#pragma once

#include "cellular-automata/Index.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace CellularAutomata {

class ArrayMapper {
public:
    ArrayMapper() = default;

    ArrayMapper(const ArrayMapper &) = default;

    ArrayMapper(ArrayMapper &&) = default;

    ArrayMapper & operator=(const ArrayMapper &) = delete;

    ArrayMapper & operator=(ArrayMapper &&) = delete;

    virtual ~ArrayMapper() = default;

    virtual bool exists(const Index & index) const = 0;

    virtual unsigned char * operator()(const Index & index) = 0;

    virtual const unsigned char * operator()(const Index & index) const = 0;

    virtual std::shared_ptr<ArrayMapper> clone() const = 0;

    virtual const std::vector<Index> & indexes() const = 0;
};

}
