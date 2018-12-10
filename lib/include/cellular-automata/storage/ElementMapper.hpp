#pragma once

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace CellularAutomata {

struct ElementsDefinition {
    enum class Type {
        BOOL, INT, REAL
    };

    inline std::pair<Type, std::size_t> & operator[](const std::size_t & i) { return m_elements[i]; }

    inline const std::pair<Type, std::size_t> & operator[](const std::size_t & i) const { return m_elements[i]; }

    inline std::size_t size() const { return m_elements.size(); }

    std::vector<std::pair<Type, std::size_t>> m_elements;
};

class ElementMapper {
public:
    explicit ElementMapper(ElementsDefinition definition);

    template<typename T>
    T & map(unsigned char * ptr, std::size_t elementIndex = 0);

    template<typename T>
    const T & map(const unsigned char * ptr, std::size_t elementIndex = 0);

private:
    std::shared_ptr<void> m_impl;
};

}
