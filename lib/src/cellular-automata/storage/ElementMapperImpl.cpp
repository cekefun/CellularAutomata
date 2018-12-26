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
        if (elementIndex >= m_definition.num_elements()) {
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

int8_t & ElementMapperImpl::as_int8(unsigned char * ptr, size_t elementIndex) {
    if (verify) {
        if (elementIndex >= m_definition.num_elements()) {
            throw logic_error("Invalid element access: invalid index");
        }
    }

    auto def = m_definition[elementIndex];

    if (verify) {
        if (def.first != Type::INT8) {
            throw logic_error("Invalid element access: wrong type");
        }
    }

    return *reinterpret_cast<int8_t *>(ptr + def.second);
}

int16_t & ElementMapperImpl::as_int16(unsigned char * ptr, size_t elementIndex) {
    if (verify) {
        if (elementIndex >= m_definition.num_elements()) {
            throw logic_error("Invalid element access: invalid index");
        }
    }

    auto def = m_definition[elementIndex];

    if (verify) {
        if (def.first != Type::INT16) {
            throw logic_error("Invalid element access: wrong type");
        }
    }

    return *reinterpret_cast<int16_t *>(ptr + def.second);
}

int32_t & ElementMapperImpl::as_int32(unsigned char * ptr, size_t elementIndex) {
    if (verify) {
        if (elementIndex >= m_definition.num_elements()) {
            throw logic_error("Invalid element access: invalid index");
        }
    }

    auto def = m_definition[elementIndex];

    if (verify) {
        if (def.first != Type::INT32) {
            throw logic_error("Invalid element access: wrong type");
        }
    }

    return *reinterpret_cast<int32_t *>(ptr + def.second);
}

int64_t & ElementMapperImpl::as_int64(unsigned char * ptr, size_t elementIndex) {
    if (verify) {
        if (elementIndex >= m_definition.num_elements()) {
            throw logic_error("Invalid element access: invalid index");
        }
    }

    auto def = m_definition[elementIndex];

    if (verify) {
        if (def.first != Type::INT64) {
            throw logic_error("Invalid element access: wrong type");
        }
    }

    return *reinterpret_cast<int64_t *>(ptr + def.second);
}

double & ElementMapperImpl::as_real(unsigned char * ptr, size_t elementIndex) {
    if (verify) {
        if (elementIndex >= m_definition.num_elements()) {
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
