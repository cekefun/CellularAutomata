#pragma once

#include <cstddef>
#include <memory>

namespace CellularAutomata {

class IFlexibleArrayImpl {
public:
    using value_type = unsigned char;
    using reference = unsigned char &;
    using const_reference = const unsigned char &;
    using iterator = unsigned char *;
    using const_iterator = const unsigned char *;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    virtual ~IFlexibleArrayImpl() noexcept = default;

    virtual unsigned char * operator[](std::size_t index) noexcept = 0;

    virtual const unsigned char * operator[](std::size_t index) const noexcept = 0;

    virtual std::shared_ptr<IFlexibleArrayImpl> clone() const = 0;

    virtual std::size_t allocated_bytes() const noexcept = 0;

    virtual iterator begin() noexcept = 0;

    virtual const_iterator begin() const noexcept = 0;

    virtual const_iterator cbegin() const noexcept = 0;

    virtual iterator end() noexcept = 0;

    virtual const_iterator end() const noexcept = 0;

    virtual const_iterator cend() const noexcept = 0;

    virtual size_type size() const noexcept = 0;
};

}
