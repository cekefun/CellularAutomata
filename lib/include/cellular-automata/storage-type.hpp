#pragma once

#include "cellular-automata/index-space.hpp"

#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace CellularAutomata {

template<typename KT, typename SP>
class IStorage {
public:
    using key_type = KT;
    using mapped_type = SP;
    using value_type = std::pair<const key_type, mapped_type>;

    virtual ~IStorage() = default;

    virtual mapped_type & operator[](const key_type &) = 0;

    virtual const mapped_type & operator[](const key_type &) const = 0;

    // Helper function
    template<typename... T>
    mapped_type & operator()(T && ... t) {
        return operator[](KT(std::forward<T>(t)...));
    }
};

}
