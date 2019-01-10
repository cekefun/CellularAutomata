#include "cellular-automata/storage/ElementMapper.hpp"

using namespace std;

namespace CellularAutomata {

using Type = ElementsDefinition::Type;

ElementMapper::ElementMapper(ElementsDefinition definition)
    : m_definition(move(definition)) {}
/*
template<>
bool & ElementMapper::map<bool>(unsigned char * ptr, size_t elementIndex) {
#if CellularAutomata_ElementMapper_Verify
    if (elementIndex >= m_definition.num_elements()) {
        throw logic_error("Invalid element access: invalid index");
    }
#endif

    auto def = m_definition[elementIndex];

#if CellularAutomata_ElementMapper_Verify
    if (def.first != Type::BOOL) {
        throw logic_error("Invalid element access: wrong type");
    }
#endif

    return *reinterpret_cast<bool *>(ptr + def.second);
}

template<>
int8_t & ElementMapper::map<int8_t>(unsigned char * ptr, size_t elementIndex) {
#if CellularAutomata_ElementMapper_Verify
    if (elementIndex >= m_definition.num_elements()) {
        throw logic_error("Invalid element access: invalid index");
    }
#endif

    auto def = m_definition[elementIndex];

#if CellularAutomata_ElementMapper_Verify
    if (def.first != Type::INT8) {
        throw logic_error("Invalid element access: wrong type");
    }
#endif

    return *reinterpret_cast<int8_t *>(ptr + def.second);
}

template<>
int16_t & ElementMapper::map<int16_t>(unsigned char * ptr, size_t elementIndex) {
#if CellularAutomata_ElementMapper_Verify
    if (elementIndex >= m_definition.num_elements()) {
        throw logic_error("Invalid element access: invalid index");
    }
#endif

    auto def = m_definition[elementIndex];

#if CellularAutomata_ElementMapper_Verify
    if (def.first != Type::INT16) {
        throw logic_error("Invalid element access: wrong type");
    }
#endif

    return *reinterpret_cast<int16_t *>(ptr + def.second);
}

template<>
int32_t & ElementMapper::map<int32_t>(unsigned char * ptr, size_t elementIndex) {
#if CellularAutomata_ElementMapper_Verify
    if (elementIndex >= m_definition.num_elements()) {
        throw logic_error("Invalid element access: invalid index");
    }
#endif

    auto def = m_definition[elementIndex];

#if CellularAutomata_ElementMapper_Verify
    if (def.first != Type::INT32) {
        throw logic_error("Invalid element access: wrong type");
    }
#endif

    return *reinterpret_cast<int32_t *>(ptr + def.second);
}

template<>
int64_t & ElementMapper::map<int64_t>(unsigned char * ptr, size_t elementIndex) {
#if CellularAutomata_ElementMapper_Verify
    if (elementIndex >= m_definition.num_elements()) {
        throw logic_error("Invalid element access: invalid index");
    }
#endif

    auto def = m_definition[elementIndex];

#if CellularAutomata_ElementMapper_Verify
    if (def.first != Type::INT64) {
        throw logic_error("Invalid element access: wrong type");
    }
#endif

    return *reinterpret_cast<int64_t *>(ptr + def.second);
}

template<>
double & ElementMapper::map<double>(unsigned char * ptr, size_t elementIndex) {
#if CellularAutomata_ElementMapper_Verify
    if (elementIndex >= m_definition.num_elements()) {
        throw logic_error("Invalid element access: invalid index");
    }
#endif

    auto def = m_definition[elementIndex];

#if CellularAutomata_ElementMapper_Verify
    if (def.first != Type::REAL) {
        throw logic_error("Invalid element access: wrong type");
    }
#endif

    return *reinterpret_cast<double *>(ptr + def.second);
}
*/
}
