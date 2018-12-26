#include <stdexcept>

#include "cellular-automata/storage/ArrayMapper1D.hpp"

using namespace std;

namespace {
inline size_t map(int64_t min, int64_t, const CellularAutomata::Index & index) {
    return static_cast<size_t>(index.x - min);
}
}

namespace CellularAutomata {
ArrayMapper1D::ArrayMapper1D(size_t elementSize, int64_t min, int64_t max)
    : m_min(min), m_max(max), m_elementSize(elementSize), m_indexes(), m_array(elementSize, static_cast<size_t>(max - min)) {

    m_indexes.reserve(static_cast<size_t>(max - min));

    for (int64_t i = min; i < max; ++i) {
        m_indexes.emplace_back(Index { i });
    }
}

ArrayMapper1D::ArrayMapper1D(const ArrayMapper1D & o)
    : m_min(o.m_min),
      m_max(o.m_max),
      m_elementSize(o.m_elementSize),
      m_indexes(o.m_indexes),
      m_array(o.m_array) {}

ArrayMapper1D::ArrayMapper1D(ArrayMapper1D && o) noexcept
    : m_min(o.m_min),
      m_max(o.m_max),
      m_elementSize(o.m_elementSize),
      m_indexes(move(o.m_indexes)),
      m_array(move(o.m_array)) {}

bool ArrayMapper1D::exists(const Index & index) const {
    if (index.dimensionality != Index::Dimensionality::ONE) {
        throw logic_error("Invalid index dimension");
    }

    return index.x >= m_min && index.x < m_max;
}

unsigned char * ArrayMapper1D::operator()(const Index & index) {
    if (index.dimensionality != Index::Dimensionality::ONE) {
        throw logic_error("Invalid index dimension");
    }
    return m_array[map(m_min, m_max, index)];
}

const unsigned char * ArrayMapper1D::operator()(const Index & index) const {
    if (index.dimensionality != Index::Dimensionality::ONE) {
        throw logic_error("Invalid index dimension");
    }
    return m_array[map(m_min, m_max, index)];
}

shared_ptr<ArrayMapper> ArrayMapper1D::clone() const {
    return make_shared<ArrayMapper1D>(*this);
}

const vector<Index> & ArrayMapper1D::indexes() const {
    return m_indexes;
}

}
