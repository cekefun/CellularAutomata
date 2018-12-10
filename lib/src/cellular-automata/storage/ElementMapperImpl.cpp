#include "cellular-automata/storage/ElementMapperImpl.hpp"

using namespace std;

namespace CellularAutomata {

using Type = ElementsDefinition::Type;

constexpr bool verify = false;

// Suppress warnings about verify being false/true
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCSimplifyInspection"
#pragma ide diagnostic ignored "OCDFAInspection"

ElementMapperImpl::ElementMapperImpl(ElementsDefinition definition)
    : m_definition(move(definition)) {}

bool & ElementMapperImpl::as_bool(unsigned char * ptr, size_t elementIndex) {
    if (verify) {
        if (elementIndex >= m_definition.size()) {
            throw logic_error("Invalid element access: invalid index");
        }
    }

    auto def = m_definition[elementIndex];

    if (verify) {
        if (def.first != Type::BOOL) {
            throw logic_error("Invalid element access: wrong type");
        }
    }

    return *reinterpret_cast<bool *>(ptr + def.second);
}

int64_t & ElementMapperImpl::as_int(unsigned char * ptr, size_t elementIndex) {
    if (verify) {
        if (elementIndex >= m_definition.size()) {
            throw logic_error("Invalid element access: invalid index");
        }
    }

    auto def = m_definition[elementIndex];

    if (verify) {
        if (def.first != Type::INT) {
            throw logic_error("Invalid element access: wrong type");
        }
    }

    return *reinterpret_cast<int64_t *>(ptr + def.second);
}

double & ElementMapperImpl::as_real(unsigned char * ptr, size_t elementIndex) {
    if (verify) {
        if (elementIndex >= m_definition.size()) {
            throw logic_error("Invalid element access: invalid index");
        }
    }

    auto def = m_definition[elementIndex];

    if (verify) {
        if (def.first != Type::REAL) {
            throw logic_error("Invalid element access: wrong type");
        }
    }

    return *reinterpret_cast<double *>(ptr + def.second);
}

#pragma clang diagnostic pop

}
