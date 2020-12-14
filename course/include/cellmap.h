#ifndef CELLMAP_H
#define	CELLMAP_H

#include "cell.h"

namespace ekumen {
namespace simulation {

class CellMap {
    public:
        CellMap() = default;
        CellMap(int rows, int cols);
        std::shared_ptr<Cell>& GetCell(int row, int col);
        int rows();
        int cols();

        friend std::ostream& operator<<(std::ostream& os, CellMap& cellmap) {
            os << "Cellmap: " << std::endl;
            for (int i = 0; i < cellmap.rows(); i++) {
                os << "[";
                for (int j = 0; j < cellmap.cols(); j++) {
                    char print_value;
                    if (cellmap.GetCell(i, j)->IsFree()) {
                        print_value = '0';
                    } else {
                        print_value = InsectTypeToChar(cellmap.GetCell(i, j)->GetInsect()->GetInsectType());
                    }
                    os << "[" << print_value;
                    os << "]";
                }
                os << "]" << std::endl;
            }
            return os;
        }

    private:
        // Sets the SurroundingCells for each Cell.
        void SetSurroundingCells();
        std::vector<std::pair<int,int>> GetSurroundingIndexes(int row, int col);
        int n_rows{0};
        int n_cols{0};
        std::vector<std::vector<std::shared_ptr<Cell>>> cells;
};
}  // namespace simulation
}  // namespace ekumen
#endif
