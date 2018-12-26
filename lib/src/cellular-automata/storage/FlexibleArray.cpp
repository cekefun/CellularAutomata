#include "cellular-automata/storage/FlexibleArray.hpp"

#include "FlexibleArrayImpl.cpp"

using namespace std;

namespace CellularAutomata {

FlexibleArray::FlexibleArray(size_t elementSize, size_t numElements)
    : m_elementSize(elementSize),
      m_numElements(numElements),
    // Could use different implementation based on requirements?
      m_impl(make_shared<AlignedFlexibleArrayImpl>(elementSize * numElements)) {}

FlexibleArray::FlexibleArray(const FlexibleArray & o)
    : m_elementSize(o.m_elementSize),
      m_numElements(o.m_numElements),
      m_impl(reinterpret_cast<IFlexibleArrayImpl *>(o.m_impl.get())->clone()) {}

FlexibleArray::FlexibleArray(FlexibleArray && o) noexcept
    : m_elementSize(o.m_elementSize),
      m_numElements(o.m_numElements),
      m_impl(move(o.m_impl)) {}

unsigned char * FlexibleArray::operator[](size_t index) {
    return (*reinterpret_cast<IFlexibleArrayImpl *>(m_impl.get()))[index * m_elementSize];
}

const unsigned char * FlexibleArray::operator[](size_t index) const {
    return (*reinterpret_cast<const IFlexibleArrayImpl *>(m_impl.get()))[index * m_elementSize];
}

}
