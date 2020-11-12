#include <cmath>
#include <sstream>
#include <string>
#include <memory>

#include "gtest/gtest.h"

#include "ant.h"
#include "cell_mock.h"

namespace ekumen {
namespace simulation {
namespace test {
namespace {

GTEST_TEST(AntTest, OccupiedCellOnInitialization) {
  std::shared_ptr<Cell> cell(new Cell());
  Ant ant(cell);
  EXPECT_FALSE(cell->IsFree());
}

GTEST_TEST(AntTest, CallbackAssignedCorrectly) {
  std::shared_ptr<Cell> cell(new Cell());
  Ant ant = Ant(cell);
  bool lambda_called{false};
  auto callback = [&lambda_called](InsectCallbackMetrics& metrics) {
        lambda_called = true;
  };
  ant.SetRoundResultsCallback(callback);
  ant.RunRound();

  EXPECT_TRUE(lambda_called);
}

GTEST_TEST(AntTest, IsAliveOnInit) {
  std::shared_ptr<Cell> cell(new Cell());
  Ant ant = Ant(cell);
  bool is_dead{false};
  auto callback = [&is_dead](InsectCallbackMetrics& metrics) {
        if (metrics.IsDead()) {
          is_dead = true;
        }
  };

  ant.SetRoundResultsCallback(callback);
  ant.RunRound();
  EXPECT_FALSE(is_dead);
}

GTEST_TEST(AntTest, IsDeadWhenToldToDie) {
  std::shared_ptr<Cell> cell(new Cell());
  Ant ant = Ant(cell);
  bool is_dead{false};
  auto callback = [&is_dead](InsectCallbackMetrics& metrics) {
        if (metrics.IsDead()) {
          is_dead = true;
        }
  };

  ant.SetRoundResultsCallback(callback);
  ant.RunRound();
  EXPECT_FALSE(is_dead);
  ant.Die();
  ant.RunRound();
  EXPECT_TRUE(is_dead);
}

GTEST_TEST(AntTest, AntMovedToOtherCell) {
  std::shared_ptr<Cell> free_cell(new Cell());
  SurroundingCells surr({free_cell, free_cell, free_cell, free_cell});
  std::shared_ptr<Cell> center_cell(new Cell());
  center_cell->SetSurroundingCells(surr);
  Ant moving_ant(center_cell);

  moving_ant.RunRound();

  EXPECT_FALSE(free_cell->IsFree());
  EXPECT_TRUE(center_cell->IsFree());
}

GTEST_TEST(AntTest, AntDidntMoveWhenCantMove) {
  std::shared_ptr<Cell> occupied_cell(new Cell());
  Ant occupying_ant(occupied_cell);
  // We'll surround the cell with an occupied cell, so that the ant can't move.
  SurroundingCells surr({occupied_cell, occupied_cell, occupied_cell, occupied_cell});
  std::shared_ptr<Cell> surrounded_cell(new Cell());
  surrounded_cell->SetSurroundingCells(surr);
  Ant surrounded_ant(surrounded_cell);

  EXPECT_EQ(surrounded_ant.GetCell().get(), surrounded_cell.get());
}

GTEST_TEST(AntTest, BreedAfter3RoundsNotBefore) {
  std::shared_ptr<Cell> free_cell(new Cell());
  // We must provide a cell where the ant can breed.
  SurroundingCells surr({free_cell, free_cell, free_cell, free_cell});
  std::shared_ptr<Cell> cell(new Cell());
  SurroundingCells surr_free({cell, cell, cell, cell});
  cell->SetSurroundingCells(surr);
  free_cell->SetSurroundingCells(surr_free);
  Ant ant(cell);
  bool has_bred{false};
  auto callback = [&has_bred](InsectCallbackMetrics& metrics) {
        if (metrics.HasBred()) {
          has_bred = true;
        }
  };
  ant.SetRoundResultsCallback(callback);

  ant.RunRound();
  EXPECT_FALSE(has_bred);
  ant.RunRound();
  EXPECT_FALSE(has_bred);
  ant.RunRound();
  EXPECT_TRUE(has_bred);
}
}  // namespace
}  // namespace test
}  // namespace simulation
}  // namespace ekumen


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
