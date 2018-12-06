#include "cellular-automata/index-space.hpp"

namespace CellularAutomata {
namespace IndexSpace {

template<>
const OneDimensional zero<OneDimensional>::value { 0 };

template<>
const TwoDimensional zero<TwoDimensional>::value { 0, 0 };

}
}
