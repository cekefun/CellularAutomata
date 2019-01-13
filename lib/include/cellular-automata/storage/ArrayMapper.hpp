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

    virtual bool exists(const Index & index) const noexcept = 0;

    virtual unsigned char * operator()(const Index & index) noexcept = 0;

    inline const unsigned char * operator()(const Index & index) const noexcept {
        return const_cast<ArrayMapper *>(this)->operator()(index);
    }

    virtual std::shared_ptr<ArrayMapper> clone() const = 0;

    virtual const std::vector<Index> & indexes() const = 0;

    virtual Index::Dimensionality getDimensionality() const noexcept = 0;

    virtual bool isInfinite() const noexcept = 0;
};

}
