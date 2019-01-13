#pragma once

#include <cstdint>

namespace CellularAutomata {

struct Index {
    enum class Dimensionality : std::uint8_t {
        ONE, TWO, THREE
    };

    inline static constexpr Index make(std::int64_t x) noexcept {
        return Index { x, 0, 0, Dimensionality::ONE };
    }

    inline static constexpr Index make(std::int64_t x, std::int64_t y) noexcept {
        return Index { x, y, 0, Dimensionality::TWO };
    }

    inline static constexpr Index make(std::int64_t x, std::int64_t y, std::int64_t z) noexcept {
        return Index { x, y, z, Dimensionality::THREE };
    }

    inline bool operator==(const Index & other) const noexcept {
        if (dimensionality != other.dimensionality) {
            return false;
        } else if (x != other.x) {
            return false;
        } else if (dimensionality > Dimensionality::ONE && y != other.y) {
            return false;
        } else if (dimensionality > Dimensionality::TWO && z != other.z) {
            return false;
        }
        return true;
    }

    inline bool operator!=(const Index & other) const noexcept {
        return !operator==(other);
    }

    inline bool operator<(const Index & other) const noexcept {
        if (dimensionality < other.dimensionality) {
            return true;
        } else if (dimensionality == other.dimensionality) {
            if (x < other.x) {
                return true;
            } else if (dimensionality > Dimensionality::ONE && x == other.x) {
                if (y < other.y) {
                    return true;
                } else if (dimensionality > Dimensionality::TWO && y == other.y) {
                    return z < other.z;
                }
            }
        }
        return false;
    }

    inline bool operator>(const Index & other) const noexcept {
        if (dimensionality > other.dimensionality) {
            return true;
        } else if (dimensionality == other.dimensionality) {
            if (x > other.x) {
                return true;
            } else if (dimensionality > Dimensionality::ONE && x == other.x) {
                if (y > other.y) {
                    return true;
                } else if (dimensionality > Dimensionality::TWO && y == other.y) {
                    return z > other.z;
                }
            }
        }
        return false;
    }

    inline bool operator<=(const Index & other) const noexcept {
        return operator==(other) || operator<(other);
    }

    inline bool operator>=(const Index & other) const noexcept {
        return operator==(other) || operator>(other);
    }

    inline constexpr Index operator+(const Index & other) const noexcept {
        return Index { x + other.x, y + other.y, z + other.z, dimensionality };
    }

    inline constexpr Index operator-(const Index & other) const noexcept {
        return Index { x - other.x, y - other.y, z - other.z, dimensionality };
    }

    std::int64_t x;
    std::int64_t y;
    std::int64_t z;

    const Dimensionality dimensionality;
};

}
