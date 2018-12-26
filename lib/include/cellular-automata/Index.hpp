#pragma once

#include <cstdint>

namespace CellularAutomata {

struct Index {
    enum class Dimensionality : unsigned char {
        ONE, TWO, THREE
    };

    inline constexpr explicit Index(std::int64_t x)
        : x(x), y(0), z(0), dimensionality(Dimensionality::ONE) {}

    inline constexpr Index(std::int64_t x, std::int64_t y)
        : x(x), y(y), z(0), dimensionality(Dimensionality::TWO) {}

    inline constexpr Index(std::int64_t x, std::int64_t y, std::int64_t z)
        : x(x), y(y), z(z), dimensionality(Dimensionality::THREE) {}

    inline bool operator==(const Index & other) const {
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

    inline bool operator!=(const Index & other) const {
        return !operator==(other);
    }

    inline bool operator<(const Index & other) const {
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

    inline bool operator>(const Index & other) const {
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

    inline bool operator<=(const Index & other) const {
        return operator==(other) || operator<(other);
    }

    inline bool operator>=(const Index & other) const {
        return operator==(other) || operator>(other);
    }

    inline Index operator+(const Index & other) const {
        if (dimensionality == Dimensionality::ONE) {
            return Index { x + other.x };
        } else if (dimensionality == Dimensionality::TWO) {
            return Index { x + other.x, y + other.y };
        } else {
            return Index { x + other.x, y + other.y, z + other.z };
        }
    }

    inline Index operator-(const Index & other) const {
        if (dimensionality == Dimensionality::ONE) {
            return Index { x - other.x };
        } else if (dimensionality == Dimensionality::TWO) {
            return Index { x - other.x, y - other.y };
        } else {
            return Index { x - other.x, y - other.y, z - other.z };
        }
    }

    std::int64_t x;
    std::int64_t y;
    std::int64_t z;

    const Dimensionality dimensionality;
};

}
