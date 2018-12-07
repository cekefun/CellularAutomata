#include "cellular-automata/FlexibleArrayImpl.hpp"

#include <algorithm>
#include <type_traits>

namespace CellularAutomata {

class AlignedFlexibleArrayImpl : public IFlexibleArrayImpl {
public:
    explicit AlignedFlexibleArrayImpl(std::size_t size)
        : m_size(size),
          m_storage(new storage_type[calcSize(size)]) {
        for (auto it = begin(); it != end(); ++it) {
            auto v = static_cast<unsigned char>(reinterpret_cast<std::size_t>(it) % 16);
            *it = v << 4 | static_cast<unsigned char>(0xAu);
        }
        for (auto it = end(); it != begin() + allocated_bytes(); ++it) {
            auto v = static_cast<unsigned char>(reinterpret_cast<std::size_t>(it) % 16);
            *it = v << 4 | static_cast<unsigned char>(0xEu);
        }
    }

    ~AlignedFlexibleArrayImpl() override {
        delete[] m_storage;
    }

    unsigned char * operator[](std::size_t index) override {
        return reinterpret_cast<unsigned char *>(m_storage) + index;
    }

    std::size_t allocated_bytes() const override {
        return sizeof(storage_type) * calcSize(m_size);
    }

    virtual iterator begin() override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    virtual const_iterator begin() const override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    virtual const_iterator cbegin() const override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    virtual iterator end() override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    virtual const_iterator end() const override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    virtual const_iterator cend() const override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    virtual size_type size() const override {
        return m_size;
    }

private:
    using storage_type = typename std::aligned_storage<sizeof(unsigned char), 16>::type;

    std::size_t m_size;
    storage_type * m_storage;

    static std::size_t calcSize(std::size_t size) {
        if (size % sizeof(storage_type) == 0) {
            return size / sizeof(storage_type);
        }
        return size / sizeof(storage_type) + 1;
    }
};

}
