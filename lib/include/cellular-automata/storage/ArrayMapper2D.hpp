#pragma once

#include "ArrayMapper.hpp"
#include "FlexibleArray.hpp"

#include <cstdint>

namespace CellularAutomata {

/**
 * Creates an array that stores <code>max - min</code> elements in the range <code>[min, max)</code>.
 */
class ArrayMapper2D : public ArrayMapper {
public:
    ArrayMapper2D(std::size_t elementSize, std::int64_t minX, std::int64_t minY, std::int64_t maxX, std::int64_t maxY);

    ArrayMapper2D(const ArrayMapper2D & o);

    ArrayMapper2D(ArrayMapper2D && o) noexcept;

    bool exists(const Index & index) const noexcept override;

    unsigned char * operator()(const Index & index) noexcept override ;

    std::shared_ptr<ArrayMapper> clone() const override;

    const std::vector<Index> & indexes() const override;

    inline Index::Dimensionality getDimensionality() const noexcept override { return Index::Dimensionality::TWO; }

    inline bool isInfinite() const noexcept override { return false; }

    inline const FlexibleArray & _backend() const { return m_array; }

private:
    std::int64_t m_minX;
    std::int64_t m_minY;
    std::int64_t m_maxX;
    std::int64_t m_maxY;
    std::uint8_t m_offsetY;
    std::size_t m_elementSize;
    std::vector<Index> m_indexes;
    FlexibleArray m_array;
};

}
