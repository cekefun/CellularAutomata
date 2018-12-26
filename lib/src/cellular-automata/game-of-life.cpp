#include "cellular-automata/game-of-life.hpp"

#include <sstream>

namespace {
std::vector<std::vector<bool>> makeCells(std::uint32_t width, std::uint32_t height) {
    std::vector<bool> row(width, false);
    return std::vector<std::vector<bool>>(height, row);
}
}

namespace CellularAutomata {
CellReference & CellReference::operator=(bool value) {
    this->ref->set(this->row, this->column, value);
    return *this;
}

CellReference::operator bool() const {
    return this->ref->get(this->row, this->column);
}

CellReference::CellReference(const GameOfLife * ref, std::uint32_t row, std::uint32_t column)
    : ref(const_cast<GameOfLife *>(ref)),
      row(row),
      column(column) {}

GameOfLife::GameOfLife(std::uint32_t width, std::uint32_t height)
    : width(width),
      height(height),
      cells(makeCells(width, height)) {}

bool GameOfLife::timeStep() {
    bool changed = false;
    std::vector<std::vector<bool>> copy = this->cells;

    for (std::uint32_t row = 0; row < height; ++row) {
        for (std::uint32_t column = 0; column < width; ++column) {
            bool alive = copy[row][column];
            std::uint8_t neighbours = this->numNeighbours(row, column);

            if (!alive && neighbours == 3) {
                copy[row][column] = true;
                changed = true;
            } else if (alive && (neighbours < 2 || neighbours > 3)) {
                copy[row][column] = false;
                changed = true;
            }
        }
    }

    if (changed) {
        this->cells = std::move(copy);

        return true;
    }

    return false;
}

std::string GameOfLife::toString() {
    std::stringstream ss;

    for (std::uint32_t row = 0; row < height; ++row) {
        for (std::uint32_t column = 0; column < width; ++column) {
            ss << (this->cells[row][column] ? "o" : " ");
        }
        ss << std::endl;
    }

    return ss.str();
}

void GameOfLife::set(std::uint32_t row, std::uint32_t column, bool value) {
    this->cells[row][column] = value;
}

bool GameOfLife::get(std::uint32_t row, std::uint32_t column) const {
    return this->cells[row][column];
}

CellReference GameOfLife::operator()(std::uint32_t row, std::uint32_t column) {
    return CellReference { this, row, column };
}

const CellReference GameOfLife::operator()(std::uint32_t row, std::uint32_t column) const {
    return CellReference { this, row, column };
}

std::uint8_t GameOfLife::numNeighbours(std::uint32_t row, std::uint32_t column) const {
    std::uint8_t result = 0;
    std::uint32_t lRow = row == 0 ? height - 1 : row - 1;
    std::uint32_t uRow = row == height - 1 ? 0 : row + 1;
    std::uint32_t lCol = column == 0 ? width - 1 : column - 1;
    std::uint32_t uCol = column == width - 1 ? 0 : column + 1;

    if (this->cells[lRow][lCol]) ++result;
    if (this->cells[lRow][column]) ++result;
    if (this->cells[lRow][uCol]) ++result;
    if (this->cells[row][uCol]) ++result;
    if (this->cells[uRow][uCol]) ++result;
    if (this->cells[uRow][column]) ++result;
    if (this->cells[uRow][lCol]) ++result;
    if (this->cells[row][lCol]) ++result;

    return result;
}
}
