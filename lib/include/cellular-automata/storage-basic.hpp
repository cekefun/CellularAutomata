#pragma once

#include "cellular-automata/storage-type.hpp"

namespace CellularAutomata {

template<typename SP, typename index_t = IndexSpace::OneDimensional>
class Fixed1DStorage : public IStorage<index_t, SP> {
public:
    using key_type = typename IStorage<index_t, SP>::key_type;
    using mapped_type = typename IStorage<index_t, SP>::mapped_type;
    using value_type = typename IStorage<index_t, SP>::value_type;

private:
    using storage_type = typename std::aligned_storage<sizeof(mapped_type), alignof(mapped_type)>::type;

    static index_t calcSize(index_t min, index_t max) {
        if (max <= min) {
            throw std::length_error("Minimum value is greater than or equal to maximum value");
        }
        return max - min;
    }

public:
    Fixed1DStorage(index_t min, index_t max, const mapped_type & def)
        : m_min(min),
          m_max(max),
          m_size(calcSize(m_min, m_max)),
          m_elements(new storage_type[m_size]) {
        // Check if min < max when building debug version
        for (key_type i = 0; i < max - min; ++i) {
            new(&m_elements[i]) mapped_type(def);
        }
    }

    ~Fixed1DStorage() {
        // Deconstruct elements, theoretically this shouldn't be needed as all state space types should be POD types
        // but we'll leave it for now just to be sure.

        for (key_type i = m_max - m_min;; --i) { // Deconstruct backwards
            reinterpret_cast<mapped_type *>(&m_elements[i])->~mapped_type();

            if (i == 0) {
                // Break at the end, in case the key type is unsigned
                break;
            }
        }

        delete[] m_elements;
    }

    mapped_type & operator[](const key_type & index) {
        // Check if min <= index < max when building debug version
        return *reinterpret_cast<mapped_type *>(&m_elements[index - m_min]);
    }

    const mapped_type & operator[](const key_type & index) const {
        // Check if min <= index < max when building debug version
        return *reinterpret_cast<mapped_type *>(&m_elements[index - m_min]);
    }

    key_type size() const {
        return m_size;
    }

private:
    const index_t m_min;
    const index_t m_max;
    const index_t m_size;
    storage_type * m_elements;
};

template<typename SP, typename index_t = IndexSpace::TwoDimensional>
class Fixed2DStorage : public IStorage<index_t, SP> {
public:
    using key_type = typename IStorage<index_t, SP>::key_type;
    using mapped_type = typename IStorage<index_t, SP>::mapped_type;
    using value_type = typename IStorage<index_t, SP>::value_type;

private:
    static_assert(std::is_same<typename key_type::first_type, typename key_type::second_type>::value, "2D storage first and second index types must be same");
    using sub_key_type = typename key_type::first_type;

    static sub_key_type calcHSize(index_t min, index_t max) {
        sub_key_type maxV = std::get<0>(max);
        sub_key_type minV = std::get<0>(min);
        if (maxV <= minV) {
            throw std::length_error("Minimum and maximum points define empty or negative direction on X-axis");
        }
        return maxV - minV;
    }

    static sub_key_type calcVSize(index_t min, index_t max) {
        sub_key_type maxV = std::get<1>(max);
        sub_key_type minV = std::get<1>(min);
        if (maxV <= minV) {
            throw std::length_error("Minimum and maximum points define empty or negative direction on Y-axis");
        }
        return maxV - minV;
    }

public:
    Fixed2DStorage(index_t min, index_t max, const mapped_type & def)
        : m_min(min),
          m_max(max),
          m_hSize(calcHSize(m_min, m_max)),
          m_vSize(calcVSize(m_min, m_max)),
          m_elements(0, m_hSize * m_vSize, def) {
    }

    Fixed2DStorage(sub_key_type minX, sub_key_type minY, sub_key_type maxX, sub_key_type maxY, const mapped_type & def)
        : m_min(minX, minY),
          m_max(maxX, maxY),
          m_hSize(calcHSize(m_min, m_max)),
          m_vSize(calcVSize(m_min, m_max)),
          m_elements(0, m_hSize * m_vSize, def) {
    }

    mapped_type & operator[](const key_type & index) {
        return m_elements[(std::get<0>(index) - std::get<0>(m_min)) + (std::get<1>(index) - std::get<1>(m_min)) * m_hSize];
    }

    const mapped_type & operator[](const key_type & index) const {
        return m_elements[(std::get<0>(index) - std::get<0>(m_min)) + (std::get<1>(index) - std::get<1>(m_min)) * m_hSize];
    }

    sub_key_type size() const {
        return m_elements.size();
    }

private:
    const index_t m_min;
    const index_t m_max;
    const std::size_t m_hSize;
    const std::size_t m_vSize;
    Fixed1DStorage<SP, sub_key_type> m_elements;
};
}
