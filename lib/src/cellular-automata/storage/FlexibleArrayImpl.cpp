#include "cellular-automata/storage/FlexibleArrayImpl.hpp"

#include <algorithm>
#include <cstring>
#include <type_traits>

using namespace std;

namespace CellularAutomata {

class AlignedFlexibleArrayImpl : public IFlexibleArrayImpl {
public:
    explicit AlignedFlexibleArrayImpl(size_t size)
        : m_size(size),
          m_storage(new storage_type[calcSize(size)]) {
        /*
        for (auto it = begin(); it != end(); ++it) {
            auto v = static_cast<unsigned char>(reinterpret_cast<size_t>(it) % 16);
            *it = v << 4 | static_cast<unsigned char>(0xAu);
        }
        for (auto it = end(); it != begin() + allocated_bytes(); ++it) {
            auto v = static_cast<unsigned char>(reinterpret_cast<size_t>(it) % 16);
            *it = v << 4 | static_cast<unsigned char>(0xEu);
        }
         */
        std::fill(begin(), end(), 0);
    }

    AlignedFlexibleArrayImpl(const AlignedFlexibleArrayImpl & o)
        : m_size(o.m_size),
          m_storage(new storage_type[calcSize(m_size)]) {
        std::memcpy(m_storage, o.m_storage, allocated_bytes());
    }

    AlignedFlexibleArrayImpl(AlignedFlexibleArrayImpl && o) noexcept
        : m_size(o.m_size),
          m_storage(o.m_storage) {
        o.m_storage = nullptr;
    }

    ~AlignedFlexibleArrayImpl() override {
        delete[] m_storage;
    }

    unsigned char * operator[](size_t index) override {
        return reinterpret_cast<unsigned char *>(m_storage) + index;
    }

    const unsigned char * operator[](size_t index) const override {
        return reinterpret_cast<unsigned char *>(m_storage) + index;
    }

    shared_ptr<IFlexibleArrayImpl> clone() const override {
        return std::make_shared<AlignedFlexibleArrayImpl>(*this);
    }

    size_t allocated_bytes() const override {
        return sizeof(storage_type) * calcSize(m_size);
    }

    iterator begin() override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    const_iterator begin() const override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    const_iterator cbegin() const override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    iterator end() override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    const_iterator end() const override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    const_iterator cend() const override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    size_type size() const override {
        return m_size;
    }

private:
    using storage_type = typename aligned_storage<sizeof(unsigned char), 16>::type;

    size_t m_size;
    storage_type * m_storage;

    static size_t calcSize(size_t size) {
        if (size % sizeof(storage_type) == 0) {
            return size / sizeof(storage_type);
        }
        return size / sizeof(storage_type) + 1;
    }
};

}
