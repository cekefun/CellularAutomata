#include "cellular-automata/storage/ElementMapperImpl.hpp"

using namespace std;

namespace CellularAutomata {

ElementMapper::ElementMapper(ElementsDefinition definition)
    : m_impl(make_shared<ElementMapperImpl>(definition)) {}

template<>
bool & ElementMapper::map<bool>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_bool(ptr, elementIndex);
}

template<>
int8_t & ElementMapper::map<int8_t>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_int8(ptr, elementIndex);
}

template<>
int16_t & ElementMapper::map<int16_t>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_int16(ptr, elementIndex);
}

template<>
int32_t & ElementMapper::map<int32_t>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_int32(ptr, elementIndex);
}

template<>
int64_t & ElementMapper::map<int64_t>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_int64(ptr, elementIndex);
}

template<>
double & ElementMapper::map<double>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_real(ptr, elementIndex);
}

}
