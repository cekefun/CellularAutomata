#pragma once

#include <cstddef>
#include <memory>

namespace CellularAutomata {

class FlexibleArray {
public:
    FlexibleArray(std::size_t elementSize, std::size_t numElements);

    FlexibleArray(const FlexibleArray &);

    FlexibleArray(FlexibleArray &&) noexcept;

    FlexibleArray & operator=(const FlexibleArray &) = delete;

    FlexibleArray & operator=(FlexibleArray &&) = delete;

    unsigned char * operator[](std::size_t index) noexcept;

    const unsigned char * operator[](std::size_t index) const noexcept;

    inline void * _impl() const noexcept { return m_impl.get(); }

private:
    const std::size_t m_elementSize;
    const std::size_t m_numElements;
    std::shared_ptr<void> m_impl = nullptr;
};

}
