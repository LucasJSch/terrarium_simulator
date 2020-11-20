#ifndef CELLMAP_H
#define	CELLMAP_H

#include "cell_mock.h"

namespace ekumen {
namespace simulation {

class CellMap {
    public:
        CellMap(int rows, int cols);
        std::shared_ptr<Cell>& GetCell(int row, int col);
        int rows();
        int cols();

    private:
        // Sets the SurroundingCells for each Cell.
        void SetSurroundingCells();
        std::vector<std::pair<int,int>> GetSurroundingIndexes();
        int n_rows;
        int n_cols;
        std::vector<std::vector<std::shared_ptr<Cell>>> cells;
};
}  // namespace simulation
}  // namespace ekumen
#endif
