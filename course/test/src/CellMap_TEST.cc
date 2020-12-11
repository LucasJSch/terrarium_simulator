#include "cellmap.h"
#include "ant.h"
#include "cell_mock.h"


#include <cmath>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

namespace ekumen {
namespace simulation {
namespace test {
namespace {

using insect_ptr = std::shared_ptr<Insect>;

GTEST_TEST(CellMapTest, ReturnsExceptionOnConstructorWithNonPositiveCols) {
    ASSERT_THROW(CellMap map(0, 1), std::invalid_argument);
    ASSERT_THROW(CellMap map(-1, 1), std::invalid_argument);
}

GTEST_TEST(CellMapTest, CellMapConstructedCorrectlyWithPositiveArguments) {
    ASSERT_NO_THROW(CellMap map(1,1));
}

GTEST_TEST(CellMapTest, ReturnsExceptionOnConstructorWithNonPositiveRows) {
    ASSERT_THROW(CellMap map(1, 0), std::invalid_argument);
    ASSERT_THROW(CellMap map(1, -1), std::invalid_argument);
}

GTEST_TEST(CellMapTest, ReturnedCellsAreNotNullPointer) {
    CellMap map(2,2);
    EXPECT_TRUE(map.GetCell(0,0));
    EXPECT_TRUE(map.GetCell(0,1));
    EXPECT_TRUE(map.GetCell(1,0));
    EXPECT_TRUE(map.GetCell(1,1));
}

GTEST_TEST(CellMapTest, GetCellsAndVerifyThatReferenceIsCorrect) {
    CellMap map(1,2);
    std::shared_ptr<Cell> cell1 = map.GetCell(0,0);
    std::shared_ptr<Cell> cell2 = map.GetCell(0,1);

    EXPECT_TRUE(map.GetCell(0,0)->IsFree());
    insect_ptr ant1(new Ant());
    ant1->SetCell(cell1);
    EXPECT_FALSE(map.GetCell(0,0)->IsFree());

    EXPECT_TRUE(map.GetCell(0,1)->IsFree());
    insect_ptr ant2(new Ant());
    ant2->SetCell(cell2);
    EXPECT_FALSE(map.GetCell(0,1)->IsFree());
}

GTEST_TEST(CellMapTest, GetNegativeRowsThrowsException) {
    CellMap map(1,1);
    ASSERT_THROW(map.GetCell(-1,0), std::invalid_argument);
}

GTEST_TEST(CellMapTest, GetNegativeColsThrowsException) {
    CellMap map(1,1);
    ASSERT_THROW(map.GetCell(0,-1), std::invalid_argument);
}

GTEST_TEST(CellMapTest, GetExceededRowIndexThrowsException) {
    CellMap map(2,2);
    ASSERT_THROW(map.GetCell(2,1), std::invalid_argument);
}

GTEST_TEST(CellMapTest, GetExceededColIndexThrowsException) {
    CellMap map(2,2);
    ASSERT_THROW(map.GetCell(1,2), std::invalid_argument);
}

GTEST_TEST(CellMapTest, GetRowsIsCorrect) {
    CellMap map(7,3);
    EXPECT_EQ(map.rows(), 7);
}

GTEST_TEST(CellMapTest, GetColsIsCorrect) {
    CellMap map(7,3);
    EXPECT_EQ(map.cols(), 3);
}

}  // namespace
}  // namespace test
}  // namespace math
}  // namespace ekumen

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
