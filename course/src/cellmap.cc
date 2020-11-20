#include <iostream>

#include "cellmap.h"
#include "cell_mock.h"



namespace ekumen {
namespace simulation {

using cell_ptr = std::shared_ptr<Cell>;

CellMap::CellMap(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Invalid constructor arguments for CellMap.");
    }
    n_rows = rows;
    n_cols = cols;
    cells = std::vector<std::vector<cell_ptr>>(n_rows, std::vector<cell_ptr>(n_cols));

    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            GetCell(i,j) = cell_ptr(new Cell());
        }
    }
}

std::shared_ptr<Cell>& CellMap::GetCell(int row, int col) {
    if (row >= n_rows || col >= n_cols || row < 0 || col < 0) {
        throw std::invalid_argument("Invalid indexes in GetCell().");
    }
    return cells[row][col];
}

int CellMap::rows() {
    return n_rows;
}

int CellMap::cols() {
    return n_cols;
}

std::vector<std::pair<int,int>> CellMap::GetSurroundingIndexes(int row, int col) {
    std::vector<std::pair<int,int>> vector;
    if (row + 1 >= 0 && row + 1 <= n_rows) {
        vector.push_back(std::pair<int,int>(row + 1, col));
    }
    if (row - 1 >= 0 && row - 1 <= n_rows) {
        vector.push_back(std::pair<int,int>(row -1 , col));
    }
    if (col - 1 >= 0 && col - 1 <= n_cols) {
        vector.push_back(std::pair<int,int>(row, col - 1));
    }
    if (col + 1 >= 0 && col + 1 <= n_cols) {
        vector.push_back(std::pair<int,int>(row, col + 1));
    }
    return vector;
}

void CellMap::SetSurroundingCells() {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_rows; j++) {
            std::vector<std::pair<int,int>> indexes = GetSurroundingIndexes(i, j);
            std::vector<cell_ptr> surr_cells;
            for (const std::pair<int,int> pair : indexes) {
                surr_cells.push_back(GetCell(pair.first, pair.second));
            }
            GetCell(i, j)->SetSurroundingCells(new SurroundingCells(surr_cells));
        }
    }
}
}  // namespace simulation
}  // namespace ekumen
