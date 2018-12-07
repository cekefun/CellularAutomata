#pragma once

#include <cstdint>

namespace CellularAutomata {

class FlexibleArray {
public:
    FlexibleArray(std::size_t elementSize, std::size_t numElements);

    ~FlexibleArray();

    unsigned char * operator[](std::size_t index);

    inline void * _impl() const { return m_impl; }

private:
    const std::size_t m_elementSize;
    const std::size_t m_numElements;
    void * m_impl = nullptr;
};

}
