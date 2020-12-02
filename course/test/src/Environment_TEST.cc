#include <cmath>
#include <sstream>
#include <string>
#include <memory>

#include "gtest/gtest.h"

#include "environment.h"
#include "ant.h"
#include "cell.h"

namespace ekumen {
namespace simulation {
namespace test {
namespace {

using cell_ptr = std::shared_ptr<Cell>;

GTEST_TEST(EnvironmentTest, ThrowsExceptionOnConstructorWithNonPositiveRows) {
    ASSERT_THROW(Environment env(0, 1, 0, 0), std::invalid_argument);
    ASSERT_THROW(Environment env(-1, 1, 0, 0), std::invalid_argument);
}

GTEST_TEST(EnvironmentTest, ThrowsExceptionOnConstructorWithNonPositiveCols) {
    ASSERT_THROW(Environment env(1, 0, 0, 0), std::invalid_argument);
    ASSERT_THROW(Environment env(1, -1, 0, 0), std::invalid_argument);
}

GTEST_TEST(EnvironmentTest, ConstructorWithPositiveDimensionsDontThrowException) {
    ASSERT_NO_THROW(Environment env(1, 1, 0, 0));
}

GTEST_TEST(EnvironmentTest, ConstructorWithMoreInsectsThanCellsThrowsException) {
    ASSERT_THROW(Environment env(1, 1, 2, 2), std::invalid_argument);
}

GTEST_TEST(EnvironmentTest, SimulationFinishedWhenCreatedWithNoInsect) {
    Environment env(1, 1, 0, 0);
    EXPECT_TRUE(env.SimulationFinished());
}

GTEST_TEST(EnvironmentTest, SimulationNotFinishedWhenCreatedInsects) {
    Environment env(2, 2, 1, 1);
    EXPECT_FALSE(env.SimulationFinished());
}

GTEST_TEST(EnvironmentTest, SimulationFinishedWhenThereIsASingleCellAndASingleInsect) {
    Environment env1(1, 1, 0, 1);
    EXPECT_TRUE(env1.SimulationFinished());
    Environment env2(1, 1, 0, 1);
    EXPECT_TRUE(env2.SimulationFinished());
}

GTEST_TEST(EnvironmentTest, SimulationFinishedWhenThereAreOnlyDoodlebugs) {
    Environment env(2, 2, 0, 2);
    EXPECT_TRUE(env.SimulationFinished());
}

GTEST_TEST(EnvironmentTest, SimulationFinishedWhenThereAreOnlyAnts) {
    Environment env(2, 2, 2, 0);
    EXPECT_TRUE(env.SimulationFinished());
}

GTEST_TEST(EnvironmentTest, SimulationFinishedWhenTheDoodlebugEatsTheAntAndThereAreNoMoreInsects) {
    Environment env(1, 2, 1, 1);
    EXPECT_FALSE(env.SimulationFinished());
    env.RunRound();
    EXPECT_TRUE(env.SimulationFinished());
}

GTEST_TEST(EnvironmentTest, RunRoundReturnsAVectorOfSize2) {
    Environment env(2, 2, 2, 0);
    std::vector<InsectsRoundMetrics> vector = env.RunRound();
    EXPECT_EQ(vector.size(), (unsigned) 2);
}

}  // namespace
}  // namespace test
}  // namespace simulation
}  // namespace ekumen


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
