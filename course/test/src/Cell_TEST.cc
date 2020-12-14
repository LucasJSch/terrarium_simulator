#include <cmath>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "cell.h"
#include "ant.h"

namespace ekumen {
namespace simulation {
namespace test {
namespace {

using cell_ptr = std::shared_ptr<Cell>;
using insect_ptr = std::shared_ptr<Insect>;

GTEST_TEST(CellTest, IsFreeOnInit) {
  cell_ptr cell(new Cell());
  EXPECT_TRUE(cell->IsFree());
}

GTEST_TEST(CellTest, IsNotFreeWhenOcuppied) {
  cell_ptr cell(new Cell());
  insect_ptr ant(new Ant());
  cell->Occupy(ant);
  EXPECT_FALSE(cell->IsFree());
}

GTEST_TEST(CellTest, IsFreeWhenFreedAfterOcuppy) {
  cell_ptr cell(new Cell());
  insect_ptr ant(new Ant());
  cell->Occupy(ant);
  cell->Free();
  EXPECT_TRUE(cell->IsFree());
}

GTEST_TEST(CellTest, HasNoSurroundingCellsOnInitialization) {
  cell_ptr cell(new Cell());
  SurroundingCells surr = cell->GetSurroundingCells();
  EXPECT_EQ(surr.GetVectorizedCells().size(), (unsigned) 0);
}

GTEST_TEST(CellTest, HasCorrectAmountOfSurroundingCellsAfterSetSurroundingCells) {
  cell_ptr cell(new Cell());
  cell_ptr surr_cell1(new Cell());
  cell_ptr surr_cell2(new Cell());
  SurroundingCells original_surr({surr_cell1, surr_cell2});
  cell->SetSurroundingCells(original_surr);
  SurroundingCells returned_surr = cell->GetSurroundingCells();
  EXPECT_EQ(returned_surr.GetVectorizedCells().size(), original_surr.GetVectorizedCells().size());
}

GTEST_TEST(CellTest, SurroundingCellsAreReferencedCorrectly) {
  cell_ptr cell(new Cell());
  cell_ptr surr_cell1(new Cell());
  cell_ptr surr_cell2(new Cell());
  SurroundingCells original_surr({surr_cell1, surr_cell2});
  cell->SetSurroundingCells(original_surr);
  SurroundingCells returned_surr = cell->GetSurroundingCells();
  EXPECT_EQ(returned_surr.GetVectorizedCells()[0], original_surr.GetVectorizedCells()[0]);
  EXPECT_EQ(returned_surr.GetVectorizedCells()[1], original_surr.GetVectorizedCells()[1]);
  EXPECT_NE(returned_surr.GetVectorizedCells()[1], original_surr.GetVectorizedCells()[0]);
  EXPECT_NE(returned_surr.GetVectorizedCells()[0], original_surr.GetVectorizedCells()[1]);
}

GTEST_TEST(CellTest, GetInsectReturnsCorrectReference) {
  cell_ptr cell(new Cell());
  insect_ptr ant(new Ant());
  cell->Occupy(ant);
  EXPECT_EQ(ant, cell->GetInsect());
}

GTEST_TEST(CellTest, GetInsectReturnsCorrectReferenceAfterChangingInsect) {
  cell_ptr cell(new Cell());
  insect_ptr ant(new Ant());
  insect_ptr ant2(new Ant());
  cell->Occupy(ant);
  cell->Occupy(ant2);
  EXPECT_NE(ant, cell->GetInsect());
  EXPECT_EQ(ant2, cell->GetInsect());
}

}  // namespace
}  // namespace test
}  // namespace simulation
}  // namespace ekumen

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
