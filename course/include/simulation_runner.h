#ifndef SIMULATION_RUNNER_H
#define	SIMULATION_RUNNER_H

#include <memory>
#include <string>
#include <vector>

#include "environment.h"


namespace ekumen {
namespace simulation {

class SimulationRunner {
    public:
        SimulationRunner(Environment env, std::string log_file="") : env{env}, log_file{log_file} {};
        void RunSimulation();

    private:
        std::vector<InsectsRoundMetrics> RunRound();
        void LogRoundResults(std::vector<InsectsRoundMetrics> metrics);
        Environment env;
        std::string log_file;
};

}  // namespace ekumen
}  // namespace simulation
#endif
