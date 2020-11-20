#include <iostream>
#include <vector>

#include "cell_mock.h"

// Mock implementation of Cell class to use in unit tests.

namespace ekumen {
namespace simulation {

void Cell::Free() {
    isFree = true;
}

void Cell::Occupy(const std::shared_ptr<Insect>& insect) {
    this->insect = insect;
    isFree = false;
}

bool Cell::IsFree() {
    return isFree;
}

void Cell::SetSurroundingCells(const SurroundingCells& surr) {
    this->surrounding_cells = surr;
}

std::shared_ptr<Cell> Cell::GetRandomFreeSurroundingCell() {
    std::vector<std::shared_ptr<Cell>> free_cells = surrounding_cells.GetFreeCells();
    if (free_cells.size() == 0) {return nullptr;}
    return free_cells[0];
}

SurroundingCells Cell::GetSurroundingCells() {
    return surrounding_cells;
}

SurroundingCells::SurroundingCells(const std::vector<std::shared_ptr<Cell>>& cells) {
    for (const std::shared_ptr<Cell>& cell_ptr : cells) {
        this->cells.push_back(cell_ptr);
    }
}

SurroundingCells::SurroundingCells(const std::initializer_list<std::shared_ptr<Cell>>& cells) {
    for (const std::shared_ptr<Cell>& cell_ptr : cells) {
        this->cells.push_back(cell_ptr);
    }
}


std::vector<std::shared_ptr<Cell>> SurroundingCells::GetFreeCells() {
    std::vector<std::shared_ptr<Cell>> vector;
    for (std::shared_ptr<Cell>& cell : cells) {
        if ((cell) && (cell->IsFree())) {
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

std::shared_ptr<Insect> Cell::GetInsect() {
    return insect;
}


}  // namespace ekumen
}  // namespace simulation