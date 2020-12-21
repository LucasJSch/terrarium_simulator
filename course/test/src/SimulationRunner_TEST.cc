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

GTEST_TEST(SimulationRunnerTest, NoExceptionsThrownWhenSimulating) {
    // This test just checks that the class can simulate without throwing exceptions.
    // It emulates the execution of an e2e usage.
    Environment env = Environment();
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
