#pragma once

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#ifndef CellularAutomata_ElementMapper_Verify
#define CellularAutomata_ElementMapper_Verify false
#endif

namespace CellularAutomata {

struct ElementsDefinition {
    enum class Type {
        BOOL, INT8, INT16, INT32, INT64, REAL,
    };

    template<typename T>
    constexpr static Type type();

    template<Type T>
    constexpr static std::uint8_t type_size();

    inline std::pair<Type, std::size_t> & operator[](const std::size_t & i) noexcept { return m_elements[i]; }

    inline const std::pair<Type, std::size_t> & operator[](const std::size_t & i) const noexcept { return m_elements[i]; }

    inline std::size_t num_elements() const noexcept { return m_elements.size(); }

    std::vector<std::pair<Type, std::size_t>> m_elements;
};

class ElementMapper {
public:
    explicit ElementMapper(ElementsDefinition definition);

// Disable warning that ptr can be a pointer to a const value, as it causes ambiguous method calls
#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"

    template<typename T>
    T & map(unsigned char * ptr, std::size_t elementIndex = 0) {
#if CellularAutomata_ElementMapper_Verify
        if (elementIndex >= m_definition.num_elements()) {
            throw std::logic_error("Invalid element access: invalid index");
        }
#endif

        auto def = m_definition[elementIndex];

#if CellularAutomata_ElementMapper_Verify
        if (def.first != ElementsDefinition::type<T>()) {
            throw std::logic_error("Invalid element access: wrong type");
        }
#endif

        return *reinterpret_cast<T *>(ptr + def.second);
    }

#pragma clang diagnostic pop

    template<typename T>
    inline const T & map(const unsigned char * ptr, std::size_t elementIndex = 0) {
        return map<T>(const_cast<unsigned char *>(ptr), elementIndex);
    }

private:
    const ElementsDefinition m_definition;
};

template<>
constexpr ElementsDefinition::Type ElementsDefinition::type<bool>() {
    return ElementsDefinition::Type::BOOL;
}

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::BOOL>() {
    return sizeof(bool);
}

template<>
constexpr ElementsDefinition::Type ElementsDefinition::type<std::int8_t>() {
    return ElementsDefinition::Type::INT8;
}

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::INT8>() {
    return sizeof(std::int8_t);
}

template<>
constexpr ElementsDefinition::Type ElementsDefinition::type<std::int16_t>() {
    return ElementsDefinition::Type::INT16;
}

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::INT16>() {
    return sizeof(std::int16_t);
}

template<>
constexpr ElementsDefinition::Type ElementsDefinition::type<std::int32_t>() {
    return ElementsDefinition::Type::INT32;
}

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::INT32>() {
    return sizeof(std::int32_t);
}

template<>
constexpr ElementsDefinition::Type ElementsDefinition::type<std::int64_t>() {
    return ElementsDefinition::Type::INT64;
}

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::INT64>() {
    return sizeof(std::int64_t);
}

template<>
constexpr ElementsDefinition::Type ElementsDefinition::type<double>() {
    return ElementsDefinition::Type::REAL;
}

template<>
constexpr std::uint8_t ElementsDefinition::type_size<ElementsDefinition::Type::REAL>() {
    return sizeof(double);
}

}
