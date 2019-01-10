#include <stdexcept>

#include "cellular-automata/storage/ArrayMapper2D.hpp"

using namespace std;

namespace {
inline size_t map(int64_t minX, int64_t minY, int64_t, int64_t maxY, const CellularAutomata::Index & index) {
    return static_cast<size_t>(index.y - minY + (maxY - minY) * (index.x - minX));
}
}

namespace CellularAutomata {
ArrayMapper2D::ArrayMapper2D(size_t elementSize, int64_t minX, int64_t minY, int64_t maxX, int64_t maxY)
    : ArrayMapper(),
      m_minX(minX),
      m_minY(minY),
      m_maxX(maxX),
      m_maxY(maxY),
      m_elementSize(elementSize),
      m_indexes(),
      m_array(elementSize, static_cast<size_t>((maxX - minX) * (maxY - minY))) {

    m_indexes.reserve(static_cast<size_t>((maxX - minX) * (maxY - minY)));

    for (int64_t x = minX; x < maxX; ++x) {
        for (int64_t y = minY; y < maxY; ++y) {
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
      m_elementSize(o.m_elementSize),
      m_indexes(o.m_indexes),
      m_array(o.m_array) {}

ArrayMapper2D::ArrayMapper2D(ArrayMapper2D && o) noexcept
    : ArrayMapper(),
      m_minX(o.m_minX),
      m_minY(o.m_minY),
      m_maxX(o.m_maxX),
      m_maxY(o.m_maxY),
      m_elementSize(o.m_elementSize),
      m_indexes(move(o.m_indexes)),
      m_array(move(o.m_array)) {}

bool ArrayMapper2D::exists(const Index & index) const noexcept {
//    if (index.dimensionality != Index::Dimensionality::TWO) {
//        throw logic_error("Invalid index dimension");
//    }

    return index.x >= m_minX && index.x < m_maxX && index.y >= m_minY && index.y < m_maxY;
}

unsigned char * ArrayMapper2D::operator()(const Index & index) noexcept {
//    if (index.dimensionality != Index::Dimensionality::TWO) {
//        throw logic_error("Invalid index dimension");
//    }

    return m_array[map(m_minX, m_minY, m_maxX, m_maxY, index)];
}

const unsigned char * ArrayMapper2D::operator()(const Index & index) const noexcept {
//    if (index.dimensionality != Index::Dimensionality::TWO) {
//        throw logic_error("Invalid index dimension");
//    }

    return m_array[map(m_minX, m_minY, m_maxX, m_maxY, index)];
}

shared_ptr<ArrayMapper> ArrayMapper2D::clone() const {
    return make_shared<ArrayMapper2D>(*this);
}

const vector<Index> & ArrayMapper2D::indexes() const {
    return m_indexes;
}

}
