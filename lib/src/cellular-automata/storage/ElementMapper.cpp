#include "cellular-automata/storage/ElementMapperImpl.hpp"

using namespace std;

namespace CellularAutomata {

ElementMapper::ElementMapper(CellularAutomata::ElementsDefinition definition)
    : m_impl(make_shared<ElementMapperImpl>(definition)) {}

template<>
bool & ElementMapper::map<bool>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_bool(ptr, elementIndex);
}

template<>
const bool & ElementMapper::map<bool>(const unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_bool(const_cast<unsigned char *>(ptr), elementIndex);
}

template<>
int64_t & ElementMapper::map<int64_t>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_int(ptr, elementIndex);
}

template<>
const int64_t & ElementMapper::map<int64_t>(const unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_int(const_cast<unsigned char *>(ptr), elementIndex);
}

template<>
double & ElementMapper::map<double>(unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_real(ptr, elementIndex);
}

template<>
const double & ElementMapper::map<double>(const unsigned char * ptr, size_t elementIndex) {
    return reinterpret_cast<ElementMapperImpl *>(m_impl.get())->as_real(const_cast<unsigned char *>(ptr), elementIndex);
}

}
