#ifndef CELL_H
#define	CELL_H

#include <memory>
#include <vector>

#include "insect.h"


namespace ekumen {
namespace simulation {

class Insect;
class Cell;

class SurroundingCells {
    public:
        SurroundingCells() = default;
        SurroundingCells(std::vector<std::shared_ptr<Cell>>&& cells);
        SurroundingCells(std::vector<std::shared_ptr<Cell>>& cells);

        std::vector<std::shared_ptr<Cell>> GetFreeCells();
        std::vector<std::shared_ptr<Cell>> GetOccupiedCells();
        std::vector<std::shared_ptr<Cell>> cells;
};

class Cell {
    public:
        void Free();
        void Occupy(std::shared_ptr<Insect>&& insect);
        void Occupy(std::shared_ptr<Insect>& insect);
        bool IsFree();
        void SetSurroundingCells(SurroundingCells& surr);
        std::shared_ptr<Cell> GetRandomFreeCell();
        SurroundingCells GetSurroundingCells();

    private:
        bool occupied;
        std::shared_ptr<Insect> insect;
        SurroundingCells surrounding_cells;
};

}  // namespace ekumen
}  // namespace simulation
#endif
