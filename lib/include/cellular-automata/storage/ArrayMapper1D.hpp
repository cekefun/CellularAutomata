#pragma once

#include "ArrayMapper.hpp"
#include "FlexibleArray.hpp"

#include <cstdint>

namespace CellularAutomata {

/**
 * Creates an array that stores <code>max - min</code> elements in the range <code>[min, max)</code>.
 */
class ArrayMapper1D : public ArrayMapper {
public:
    ArrayMapper1D(std::size_t elementSize, std::int64_t min, std::int64_t max);

    ArrayMapper1D(const ArrayMapper1D & o);

    ArrayMapper1D(ArrayMapper1D && o) noexcept;

    bool exists(const Index & index) const override;

    unsigned char * operator()(const Index & index) override;

    const unsigned char * operator()(const Index & index) const override;

    std::shared_ptr<ArrayMapper> clone() const override;

    const std::vector<Index> & indexes() const override;

    inline Index::Dimensionality getDimensionality() const override { return Index::Dimensionality::ONE; }

    inline bool isInfinite() const override { return false; }

    inline const FlexibleArray & _backend() const { return m_array; }

private:
    std::int64_t m_min;
    std::int64_t m_max;
    std::size_t m_elementSize;
    std::vector<Index> m_indexes;
    FlexibleArray m_array;
};

}
