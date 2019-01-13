#include <stdexcept>

#include "cellular-automata/storage/ArrayMapper2D.hpp"

using namespace std;

namespace {
/*
 * Memory layout:
 *
 *  y\x     minX        ...        maxX
 *  minY    *   ------>  increasing memory location
 *          ^
 *          Base address (address 0)
 *  ...
 *
 *
 *  maxY
 *
 *  => Row major ordering
 */
inline constexpr size_t map(int64_t minX, int64_t minY, int64_t, int64_t, int8_t offsetY, const CellularAutomata::Index & index) noexcept {
    // Use bitshifts instead of multiplication to increase speed
    // Caveat: we need to use more memory
    // return static_cast<size_t>(index.x - minX + (maxX - minX) * (index.y - minY));
    return static_cast<size_t>(index.x - minX + ((index.y - minY) << offsetY));
}

uint8_t calcOffsetY(int64_t minX, int64_t maxX) {
    auto numColls = static_cast<uint64_t>(maxX - minX);

    bool powerOf2 = (numColls & (numColls - 1)) == 0;

    uint8_t bit = 63;
    while ((numColls & (1l << bit)) == 0l && bit != 0) {
        --bit;
    }

    if (bit == 63) {
        throw std::logic_error("Cannot calculate offset, not enough bits!");
    }

    return static_cast<uint8_t>(bit + (powerOf2 ? 0 : 1));
}
}

namespace CellularAutomata {
ArrayMapper2D::ArrayMapper2D(size_t elementSize, int64_t minX, int64_t minY, int64_t maxX, int64_t maxY)
    : ArrayMapper(),
      m_minX(minX),
      m_minY(minY),
      m_maxX(maxX),
      m_maxY(maxY),
      m_offsetY(calcOffsetY(minX, maxX)),
      m_elementSize(elementSize),
      m_indexes(),
      m_array(elementSize, static_cast<size_t>((1ull << m_offsetY) * (maxY - minY))) {

    m_indexes.reserve(static_cast<size_t>((maxX - minX) * (maxY - minY)));

    for (int64_t y = minY; y < maxY; ++y) {
        for (int64_t x = minX; x < maxX; ++x) {
            m_indexes.emplace_back(Index::make(x, y));
        }
    }
}

ArrayMapper2D::ArrayMapper2D(const ArrayMapper2D & o)
    : ArrayMapper(),
      m_minX(o.m_minX),
      m_minY(o.m_minY),
      m_maxX(o.m_maxX),
      m_maxY(o.m_maxY),
      m_offsetY(o.m_offsetY),
      m_elementSize(o.m_elementSize),
      m_indexes(o.m_indexes),
      m_array(o.m_array) {}

ArrayMapper2D::ArrayMapper2D(ArrayMapper2D && o) noexcept
    : ArrayMapper(),
      m_minX(o.m_minX),
      m_minY(o.m_minY),
      m_maxX(o.m_maxX),
      m_maxY(o.m_maxY),
      m_offsetY(o.m_offsetY),
      m_elementSize(o.m_elementSize),
      m_indexes(move(o.m_indexes)),
      m_array(move(o.m_array)) {}

bool ArrayMapper2D::exists(const Index & index) const noexcept {
    return index.x >= m_minX && index.x < m_maxX && index.y >= m_minY && index.y < m_maxY;
}

unsigned char * ArrayMapper2D::operator()(const Index & index) noexcept {
    return m_array[map(m_minX, m_minY, m_maxX, m_maxY, m_offsetY, index)];
}

shared_ptr<ArrayMapper> ArrayMapper2D::clone() const {
    return make_shared<ArrayMapper2D>(*this);
}

const vector<Index> & ArrayMapper2D::indexes() const {
    return m_indexes;
}

}
