#include <vector>

#include "cell_mock.h"

// Mock implementation of Cell class to use in unit tests.

namespace ekumen {
namespace simulation {

void Cell::Free() {
    occupied = true;
}

void Cell::Occupy(std::shared_ptr<Insect>&& insect) {
    this->insect = std::move(insect);
}

void Cell::Occupy(std::shared_ptr<Insect>& insect) {
    this->insect = insect;
}

bool Cell::IsFree() {
    return occupied;
}

void Cell::SetSurroundingCells(SurroundingCells& surr) {
    this->surrounding_cells = surr;
}

std::shared_ptr<Cell> Cell::GetRandomFreeCell() {
    std::vector<std::shared_ptr<Cell>> free_cells = surrounding_cells.GetFreeCells();
    if (free_cells.size() == 0) {return nullptr;}
    return free_cells[0];
}

SurroundingCells Cell::GetSurroundingCells() {
    return surrounding_cells;
}

SurroundingCells::SurroundingCells(std::vector<std::shared_ptr<Cell>>& cells) {
    for (std::shared_ptr<Cell>& cell_ptr : cells) {
        this->cells.push_back(cell_ptr);
    }
}

SurroundingCells::SurroundingCells(std::vector<std::shared_ptr<Cell>>&& cells) {
    this->cells = std::move(cells);
}

std::vector<std::shared_ptr<Cell>> SurroundingCells::GetFreeCells() {
    std::vector<std::shared_ptr<Cell>> vector;
    for (std::shared_ptr<Cell>& cell : cells) {
        if ((cell != nullptr) && (cell->IsFree())) {
            vector.push_back(cell);
        }
    }
    return vector;
}

std::vector<std::shared_ptr<Cell>> SurroundingCells::GetOccupiedCells() {
    std::vector<std::shared_ptr<Cell>> vector;
    for (std::shared_ptr<Cell>& cell : cells) {
        if ((cell != nullptr) && (!cell->IsFree())) {
            vector.push_back(cell);
        }
    }
    return vector;
}
}  // namespace ekumen
}  // namespace simulation