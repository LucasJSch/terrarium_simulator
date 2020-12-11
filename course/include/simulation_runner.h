#ifndef SIMULATION_RUNNER_H
#define	SIMULATION_RUNNER_H

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "environment.h"


namespace ekumen {
namespace simulation {

class SimulationRunner {
    public:
        SimulationRunner(Environment env, std::string log_file="") : env{env}, log_file{log_file} {
            if (!log_file.empty()) {
                this->log_file_stream.open(log_file);
            }
        }
        void RunSimulation();

    private:
        std::vector<InsectsRoundMetrics> RunRound();
        void LogRoundResults(std::vector<InsectsRoundMetrics> metrics);
        void LogToOutputFile(const std::string& str);
        void LogToOutputFile(const InsectsRoundMetrics& metrics);
        Environment env;
        std::string log_file;
        std::fstream log_file_stream;
};

}  // namespace ekumen
}  // namespace simulation
#endif
