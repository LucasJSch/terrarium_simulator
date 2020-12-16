#include <ctime>
#include <iostream>
#include <fstream>
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
    LogToOutputFile("The winner is: ");
    LogToOutputFile(InsectTypeToString(env.WhichInsectSurvived()));
    LogToOutputFile("\n");
}

std::vector<InsectsRoundMetrics> SimulationRunner::RunRound() {
    return env.RunRound();
}

void SimulationRunner::LogRoundResults(std::vector<InsectsRoundMetrics> metrics) {
    for (const InsectsRoundMetrics& metric: metrics) {
        LogToOutputFile(metric);
    }
}

void SimulationRunner::LogToOutputFile(const std::string& str) {
    if (log_file.empty()) {
        std::cout << str;
    } else {
        log_file_stream << str;
    }
}

void SimulationRunner::LogToOutputFile(const InsectsRoundMetrics& metrics) {
    if (log_file.empty()) {
        std::cout << metrics;
    } else {
        log_file_stream << metrics;
    }
}

}  // namespace ekumen
}  // namespace simulation