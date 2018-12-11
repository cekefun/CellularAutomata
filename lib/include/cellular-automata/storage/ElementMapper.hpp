#pragma once

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace CellularAutomata {

struct ElementsDefinition {
    enum class Type {
        BOOL, INT8, INT16, INT32, INT64, REAL,
    };

    template<Type T>
    constexpr static std::uint8_t type_size();

    inline std::pair<Type, std::size_t> & operator[](const std::size_t & i) { return m_elements[i]; }

    inline const std::pair<Type, std::size_t> & operator[](const std::size_t & i) const { return m_elements[i]; }

    inline std::size_t num_elements() const { return m_elements.size(); }

    std::vector<std::pair<Type, std::size_t>> m_elements;
};

class ElementMapper {
public:
    explicit ElementMapper(ElementsDefinition definition);

    template<typename T>
    T & map(unsigned char * ptr, std::size_t elementIndex = 0);

    template<typename T>
    inline const T & map(const unsigned char * ptr, std::size_t elementIndex = 0) {
        return map<T>(const_cast<unsigned char *>(ptr), elementIndex);
    }

private:
    std::shared_ptr<void> m_impl;
};

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::BOOL>() {
    return sizeof(bool);
};

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::INT8>() {
    return sizeof(std::int8_t);
};

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::INT16>() {
    return sizeof(std::int16_t);
};

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::INT32>() {
    return sizeof(std::int32_t);
};

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::INT64>() {
    return sizeof(std::int64_t);
};

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::REAL>() {
    return sizeof(double);
};

}
