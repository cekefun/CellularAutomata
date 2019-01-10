#include "cellular-automata/storage/FlexibleArrayImpl.hpp"

#include <algorithm>
#include <cstring>
#include <memory>
#include <type_traits>

#ifdef CellularAutomata_Use_Boost

#include <boost/align/aligned_allocator.hpp>

#endif

using namespace std;

namespace {
using aligned_type = typename aligned_storage<sizeof(unsigned char), alignof(std::uint64_t)>::type;

// Use aligned storage if possible to reduce the chance of page overlap happening
#ifdef CellularAutomata_Use_Boost
using allocator_type = boost::alignment::aligned_allocator<aligned_type, 512>;
#else
using allocator_type = std::allocator<aligned_type>;
#endif

allocator_type alignedAllocator;
}

namespace CellularAutomata {

class AlignedFlexibleArrayImpl : public IFlexibleArrayImpl {
public:
    explicit AlignedFlexibleArrayImpl(size_t size)
        : m_size(size),
          m_storage(reinterpret_cast<storage_type *>(alignedAllocator.allocate(calcSize(m_size)))) {
        /*
        for (auto it = begin(); it != end(); ++it) {
            auto v = static_cast<unsigned char>(reinterpret_cast<size_t>(it) % 16);
            *it = v << 4 | static_cast<unsigned char>(0xAu);
        }
        for (auto it = end(); it != begin() + allocated_bytes(); ++it) {
            auto v = static_cast<unsigned char>(reinterpret_cast<size_t>(it) % 16);
            *it = v << 4 | static_cast<unsigned char>(0xEu);
        }
        // */
        std::fill(begin(), end(), 0);
    }

    AlignedFlexibleArrayImpl(const AlignedFlexibleArrayImpl & o)
        : m_size(o.m_size),
          m_storage(reinterpret_cast<storage_type *>(alignedAllocator.allocate(calcSize(m_size)))) {
        std::memcpy(m_storage, o.m_storage, allocated_bytes());
    }

    AlignedFlexibleArrayImpl(AlignedFlexibleArrayImpl && o) noexcept
        : m_size(o.m_size),
          m_storage(o.m_storage) {
        o.m_storage = nullptr;
    }

    ~AlignedFlexibleArrayImpl() noexcept override {
        alignedAllocator.deallocate(m_storage, calcSize(m_size));
    }

    AlignedFlexibleArrayImpl & operator=(const AlignedFlexibleArrayImpl &) = delete;

    AlignedFlexibleArrayImpl & operator=(AlignedFlexibleArrayImpl &&) = delete;

    unsigned char * operator[](size_t index) noexcept override {
        return reinterpret_cast<unsigned char *>(m_storage) + index;
    }

    const unsigned char * operator[](size_t index) const noexcept override {
        return reinterpret_cast<unsigned char *>(m_storage) + index;
    }

    shared_ptr<IFlexibleArrayImpl> clone() const override {
        return std::make_shared<AlignedFlexibleArrayImpl>(*this);
    }

    size_t allocated_bytes() const noexcept override {
        return sizeof(storage_type) * calcSize(m_size);
    }

    iterator begin() noexcept override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    const_iterator begin() const noexcept override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    const_iterator cbegin() const noexcept override {
        return reinterpret_cast<unsigned char *>(m_storage);
    }

    iterator end() noexcept override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    const_iterator end() const noexcept override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    const_iterator cend() const noexcept override {
        return reinterpret_cast<unsigned char *>(m_storage) + size();
    }

    size_type size() const noexcept override {
        return m_size;
    }

private:
    using storage_type = typename decltype(::alignedAllocator)::value_type;

    size_t m_size;
    storage_type * m_storage;

    constexpr inline static size_t calcSize(size_t size) {
        return size % sizeof(storage_type) == 0 ? size / sizeof(storage_type) : size / sizeof(storage_type) + 1;
    }
};

}
