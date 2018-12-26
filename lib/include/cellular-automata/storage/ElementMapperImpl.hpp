#pragma once

#include "cellular-automata/storage/ElementMapper.hpp"

namespace CellularAutomata {

class ElementMapperImpl {
public:
    explicit ElementMapperImpl(ElementsDefinition definition);

    bool & as_bool(unsigned char * ptr, std::size_t elementIndex);

    std::int8_t & as_int8(unsigned char * ptr, std::size_t elementIndex);

    std::int16_t & as_int16(unsigned char * ptr, std::size_t elementIndex);

    std::int32_t & as_int32(unsigned char * ptr, std::size_t elementIndex);

    std::int64_t & as_int64(unsigned char * ptr, std::size_t elementIndex);

    double & as_real(unsigned char * ptr, std::size_t elementIndex);

private:
    const ElementsDefinition m_definition;
};

}
