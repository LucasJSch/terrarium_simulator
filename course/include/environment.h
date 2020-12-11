#ifndef ENVIRONMENT_H
#define	ENVIRONMENT_H

#include "cellmap.h"
#include "cell.h"
#include "insects_metrics.h"

namespace ekumen {
namespace simulation {

class Environment {
    public:
        Environment(int rows, int cols, int ants, int doodlebugs);
        Environment();
        std::vector<InsectsRoundMetrics> RunRound();
        bool SimulationFinished();
        std::shared_ptr<CellMap> GetCellMap();

    private:
        void Initialize(int rows, int cols, int ants, int doodlebugs);
        void RandomizeInsectsOrder();
        CellMap cell_map;
        std::vector<std::shared_ptr<Insect>> insects;
};
}  // namespace simulation
}  // namespace ekumen
#endif
