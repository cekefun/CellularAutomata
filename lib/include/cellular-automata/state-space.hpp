#pragma once

#include <cstdint>

namespace CellularAutomata {
namespace StateSpace {

enum class Life : std::uint8_t {
    DEAD, ALIVE
};

using DiscreteU8 = std::uint8_t;
using DiscreteS8 = std::int8_t;
using DiscreteU16 = std::uint16_t;
using DiscreteS16 = std::int16_t;
using DiscreteU32 = std::uint32_t;
using DiscreteS32 = std::int32_t;
using DiscreteU64 = std::uint64_t;
using DiscreteS64 = std::int64_t;

using ContinuousF = float;
using ContinuousD = double;

}
}
