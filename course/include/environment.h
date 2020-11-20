#ifndef ENVIRONMENT_H
#define	ENVIRONMENT_H

#include "cellmap.h"
#include "cell_mock.h"
#include "insects_metrics.h"

namespace ekumen {
namespace simulation {

class Environment {
    public:
        Environment(int rows, int cols);
        InsectMetrics RunRound();
        bool SimulationFinished();

    private:
        bool SimulationInitialized();
        void RandomizeInsectsOrder();
        CellMap cell_map;
        std::vector<std::shared_ptr<Insect>> insects;
        bool simulation_initialized{false};
        bool simulation_finished{false};
};
}  // namespace simulation
}  // namespace ekumen
#endif
