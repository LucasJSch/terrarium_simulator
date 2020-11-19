#include <cmath>
#include <sstream>
#include <string>
#include <memory>

#include "gtest/gtest.h"

#include "doodlebug.h"
#include "ant.h"
#include "cell_mock.h"

namespace ekumen {
namespace simulation {
namespace test {
namespace {

using cell_ptr = std::shared_ptr<Cell>;

GTEST_TEST(DoodlebugTest, OccupiedCellOnInitialization) {
  cell_ptr cell(new Cell());
  Doodlebug doodlebug(cell);
  EXPECT_FALSE(cell->IsFree());
}

GTEST_TEST(DoodlebugTest, CallbackAssignedCorrectly) {
  cell_ptr cell(new Cell());
  Doodlebug doodlebug = Doodlebug(cell);
  bool lambda_called{false};
  auto callback = [&lambda_called](InsectCallbackMetrics& metrics) {
        lambda_called = true;
  };
  doodlebug.SetRoundResultsCallback(callback);
  doodlebug.RunRound();

  EXPECT_TRUE(lambda_called);
}

GTEST_TEST(DoodlebugTest, IsAliveOnInit) {
  cell_ptr cell(new Cell());
  Doodlebug doodlebug = Doodlebug(cell);
  bool is_dead{false};
  auto callback = [&is_dead](InsectCallbackMetrics& metrics) {
        if (metrics.IsDead()) {
          is_dead = true;
        }
  };

  doodlebug.SetRoundResultsCallback(callback);
  doodlebug.RunRound();
  EXPECT_FALSE(is_dead);
}

GTEST_TEST(DoodlebugTest, IsDeadWhenToldToDie) {
  cell_ptr cell(new Cell());
  Doodlebug doodlebug = Doodlebug(cell);
  bool is_dead{false};
  auto callback = [&is_dead](InsectCallbackMetrics& metrics) {
        if (metrics.IsDead()) {
          is_dead = true;
        }
  };

  doodlebug.SetRoundResultsCallback(callback);
  doodlebug.RunRound();
  EXPECT_FALSE(is_dead);
  doodlebug.Die();
  doodlebug.RunRound();
  EXPECT_TRUE(is_dead);
}

GTEST_TEST(DoodlebugTest, DoodlebugMovedToOtherCell) {
  cell_ptr free_cell(new Cell());
  SurroundingCells surr({free_cell, free_cell, free_cell, free_cell});
  cell_ptr center_cell(new Cell());
  center_cell->SetSurroundingCells(surr);
  Doodlebug moving_doodlebug(center_cell);

  moving_doodlebug.RunRound();

  EXPECT_FALSE(free_cell->IsFree());
  EXPECT_TRUE(center_cell->IsFree());
}

GTEST_TEST(DoodlebugTest, DoodlebugDidntMoveWhenCantMove) {
  cell_ptr occupied_cell(new Cell());
  Doodlebug occupying_doodlebug(occupied_cell);
  // We'll surround the cell with an occupied cell, so that the doodlebug can't move.
  SurroundingCells surr({occupied_cell, occupied_cell, occupied_cell, occupied_cell});
  cell_ptr surrounded_cell(new Cell());
  surrounded_cell->SetSurroundingCells(surr);
  Doodlebug surrounded_doodlebug(surrounded_cell);

  EXPECT_EQ(surrounded_doodlebug.GetCell(), surrounded_cell);
}

GTEST_TEST(DoodlebugTest, BreedAfter8RoundsNotBefore) {
  cell_ptr cell(new Cell());
  Doodlebug doodlebug(cell);
  // In the next lines we are creating a cell surrounded by four cells.
  // Each of the surrounding cells has the first mentioned cell as it
  // surrounded cell. A simple graph to represent this:
  //                    surr_cell          surr_cell
  //
  //                                cell
  //
  //                    surr_cell          surr_cell
  // Each 'surr_cell' has a reference to 'cell', and 'cell' has a reference
  // to each 'surr_cell'.
  SurroundingCells surr = {cell_ptr(new Cell()), cell_ptr(new Cell()),
                           cell_ptr(new Cell()), cell_ptr(new Cell())};
  SurroundingCells surr2 = {cell};
  for (const cell_ptr& surr_cell : surr.cells) {
    surr_cell->SetSurroundingCells(surr2);
  }

  // Set the callback to check if the doodlebug has bred.
  cell->SetSurroundingCells(surr);
  bool has_bred{false};
  auto callback = [&has_bred](InsectCallbackMetrics& metrics) {
        if (metrics.HasBred()) {
          has_bred = true;
        }
  };
  doodlebug.SetRoundResultsCallback(callback);

  for (int i = 0; i < 7; i++) {
    cell_ptr free_cell = doodlebug.GetCell()->GetRandomFreeSurroundingCell();
    // We need to create an Ant to keep the Doodlebug alive.
    Ant ant = Ant(free_cell);
    doodlebug.RunRound();
    EXPECT_FALSE(has_bred);
  }
  doodlebug.RunRound();
  EXPECT_TRUE(has_bred);
}

GTEST_TEST(DoodlebugTest, DoodlebugDoesntEatAndDiesAfter3RoundsOfNotEating) {
  cell_ptr cell(new Cell());
  Doodlebug doodlebug(cell);
  bool is_dead{false};
  auto callback = [&is_dead](InsectCallbackMetrics& metrics) {
        if (metrics.IsDead()) {
          is_dead = true;
        }
  };
  doodlebug.SetRoundResultsCallback(callback);

  doodlebug.RunRound();
  EXPECT_FALSE(is_dead);
  doodlebug.RunRound();
  EXPECT_FALSE(is_dead);
  doodlebug.RunRound();
  EXPECT_TRUE(is_dead);
}

// This test checks that despite eating an Ant, a Doodlebug still dies after 3 rounds
// of not eating anything.
GTEST_TEST(DoodlebugTest, DoodlebugEatsAnAntButDiesAfter3RoundsOfNotEating) {
  cell_ptr doodlebug_cell(new Cell());
  cell_ptr ant_cell(new Cell());
  Ant ant(ant_cell);
  Doodlebug doodlebug(doodlebug_cell);
  SurroundingCells surr = {ant_cell};
  doodlebug_cell->SetSurroundingCells(surr);

  bool doodlebug_is_dead{false};
  auto callback = [&doodlebug_is_dead](InsectCallbackMetrics& metrics) {
        if (metrics.IsDead()) {
          doodlebug_is_dead = true;
        }
  };
  doodlebug.SetRoundResultsCallback(callback);

  for (int i = 0; i < 3; i++) {
    doodlebug.RunRound();
    ant.RunRound();
    EXPECT_FALSE(doodlebug_is_dead);
  }
  doodlebug.RunRound();
  EXPECT_TRUE(doodlebug_is_dead);
}

GTEST_TEST(DoodlebugTest, DoodlebugEatsAnt) {
  cell_ptr doodlebug_cell(new Cell());
  cell_ptr ant_cell(new Cell());
  Ant ant(ant_cell);
  Doodlebug doodlebug(doodlebug_cell);
  SurroundingCells surr = {ant_cell};
  doodlebug_cell->SetSurroundingCells(surr);

  bool ant_is_dead{false};
  auto callback = [&ant_is_dead](InsectCallbackMetrics& metrics) {
        if (metrics.IsDead()) {
          ant_is_dead = true;
        }
  };
  ant.SetRoundResultsCallback(callback);

  EXPECT_FALSE(ant_is_dead);
  doodlebug.RunRound();
  ant.RunRound();
  EXPECT_TRUE(ant_is_dead);
}

}  // namespace
}  // namespace test
}  // namespace simulation
}  // namespace ekumen


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
