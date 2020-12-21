#include <iostream>

#include "environment.h"
#include "simulation_runner.h"

using ekumen::simulation::Environment;
using ekumen::simulation::SimulationRunner;

int main(int argc, char **argv) {
  Environment env = Environment();
  SimulationRunner simulation_runner(env);
  simulation_runner.RunSimulation();
  return 0;
}
