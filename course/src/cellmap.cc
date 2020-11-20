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

}  // namespace simulation
}  // namespace ekumen
