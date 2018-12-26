#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace CellularAutomata {
class GameOfLife;

class CellReference {
public:
    CellReference & operator=(bool value);

    operator bool() const;

protected:
    friend class GameOfLife;

    CellReference(const GameOfLife * ref, std::uint32_t row, std::uint32_t column);

private:
    GameOfLife * const ref;
    const std::uint32_t row;
    const std::uint32_t column;
};

class GameOfLife {
public:
    GameOfLife(std::uint32_t width, std::uint32_t height);

    bool timeStep();

    std::string toString();

    CellReference operator()(std::uint32_t row, std::uint32_t column);

    const CellReference operator()(std::uint32_t row, std::uint32_t column) const;

protected:
    friend class CellReference;

    void set(std::uint32_t row, std::uint32_t column, bool value);

    bool get(std::uint32_t row, std::uint32_t column) const;

private:
    std::uint8_t numNeighbours(std::uint32_t row, std::uint32_t column) const;

    // Access happens cells[row][column]
    const std::uint32_t width;
    const std::uint32_t height;
    std::vector<std::vector<bool>> cells;

    // const std::vector<std::uint8_t> RULE_BORN = { 2 };
    // const std::vector<std::uint8_t> RULE_SURVIVE = { 2, 3 };
};
}
