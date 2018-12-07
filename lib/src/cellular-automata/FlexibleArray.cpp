#include "cellular-automata/FlexibleArray.hpp"

#include "FlexibleArrayImpl.cpp"

namespace CellularAutomata {

FlexibleArray::FlexibleArray(std::size_t elementSize, std::size_t numElements)
    : m_elementSize(elementSize),
      m_numElements(numElements) {
    // Could use different implementation based on requirements?
    m_impl = reinterpret_cast<void *>(new AlignedFlexibleArrayImpl(elementSize * numElements));
}

FlexibleArray::~FlexibleArray() {
    delete reinterpret_cast<IFlexibleArrayImpl *>(m_impl);
}

unsigned char * FlexibleArray::operator[](std::size_t index) {
    return (*reinterpret_cast<IFlexibleArrayImpl *>(m_impl))[index * m_elementSize];
}

}
