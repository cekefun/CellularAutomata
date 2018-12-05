#pragma once

#include <type_traits>
#include <utility>
#include <vector>

namespace CellularAutomata {
namespace neighbourhood {

template<
    typename KT,
    typename = std::enable_if<std::is_integral<KT>::value>
>
std::vector<KT> oneDimensional(const KT center) {
    std::vector<KT> result;

    result.push_back(center);
    std::get<0>(result.back()) -= 1;

    result.push_back(center);
    std::get<0>(result.back()) += 1;

    return result;
}

template<
    typename KT,
    typename = std::enable_if<std::tuple_size<KT>::value == 2>
>
std::vector<KT> moore(const KT center) {
    std::vector<KT> result;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0) {
                result.push_back(center);
                std::get<0>(result.back()) += i;
                std::get<1>(result.back()) += j;
            }
        }
    }

    return result;
}

template<
    typename KT,
    typename = std::enable_if<std::tuple_size<KT>::value == 2>
>
std::vector<KT> vonNeumann(const KT center) {
    std::vector<KT> result;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((i != 0 && j == 0) || (i == 0 && j != 0)) {
                result.push_back(center);
                std::get<0>(result.back()) += i;
                std::get<1>(result.back()) += j;
            }
        }
    }

    return result;
}

}
}
