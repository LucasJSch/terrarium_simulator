#include <ctime>
#include <iostream>
#include <vector>

#include "simulation_runner.h"

namespace ekumen {
namespace simulation {

void SimulationRunner::RunSimulation() {
    while (!env.SimulationFinished()) {
        std::vector<InsectsRoundMetrics> metrics;
        metrics = RunRound();
        LogRoundResults(metrics);
    }
}

std::vector<InsectsRoundMetrics> SimulationRunner::RunRound() {
    return env.RunRound();
}

void SimulationRunner::LogRoundResults(std::vector<InsectsRoundMetrics> metrics) {
    for (const InsectsRoundMetrics& metric: metrics) {
        // TODO: Log this to the configured file.
        if (metric.GetInsectType() == InsectType::Ant) {
            std::cout << "Ants statistics:" << std::endl;
        }
        else if (metric.GetInsectType() == InsectType::Doodlebug){
            std::cout << "Doodlebugs statistics:" << std::endl;
        } else {
            throw std::runtime_error("Undefined insect type metrics.");
        }
        std::cout << metric;
    }
}

}  // namespace ekumen
}  // namespace simulation