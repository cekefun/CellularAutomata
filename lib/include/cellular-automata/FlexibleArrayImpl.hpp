#pragma once

#include <cstdint>

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

    virtual ~IFlexibleArrayImpl() = default;

    virtual unsigned char * operator[](std::size_t index) = 0;

    virtual std::size_t allocated_bytes() const = 0;

    virtual iterator begin() = 0;

    virtual const_iterator begin() const = 0;

    virtual const_iterator cbegin() const = 0;

    virtual iterator end() = 0;

    virtual const_iterator end() const = 0;

    virtual const_iterator cend() const = 0;

    virtual size_type size() const = 0;
};

}
