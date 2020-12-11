#include <cmath>
#include <sstream>
#include <string>
#include <memory>

#include "gtest/gtest.h"

#include "simulation_runner.h"
#include "environment.h"

namespace ekumen {
namespace simulation {
namespace test {
namespace {

using cell_ptr = std::shared_ptr<Cell>;

GTEST_TEST(SimulationRunnerTest, Test) {
    Environment env(5, 5, 5, 5);
    SimulationRunner simulation_runner(env);
    simulation_runner.RunSimulation();
}

}  // namespace
}  // namespace test
}  // namespace simulation
}  // namespace ekumen


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
