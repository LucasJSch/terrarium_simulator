// This file describes a challenge of a C++ L1 Padawan. The goal
// of this unit test is to suggest an API and the abstractions
// needed to implement an isometry.

// Consider including other header files if needed.
#include "isometry.h"

#include <cmath>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

namespace ekumen {
namespace math {
namespace test {
namespace {

GTEST_TEST(Vector3Test, Vector3Operations) {
  const double kTolerance{1e-12};
  const Vector3 p{1., 2., 3.};
  const Vector3 q{4., 5., 6.};

  EXPECT_EQ(p + q, {5., 7., 9.});
  EXPECT_EQ(p - q, {-3., -3., -3.});
  EXPECT_EQ(p * 2., Vector3(2., 4., 6));
  EXPECT_EQ(2 * q, Vector3(8., 10., 12.));
  EXPECT_EQ(p * q, Vector3(4., 10., 18.));
  EXPECT_EQ(p / q, Vector3(.25, .4, .5));
  EXPECT_NEAR(p.norm(), 3.7416573867739413, kTolerance);
  EXPECT_EQ(p.x(), 1.);
  EXPECT_EQ(p.y(), 2.);
  EXPECT_EQ(p.z(), 3.);
  EXPECT_EQ(p[0], 1.);
  EXPECT_EQ(p[1], 2.);
  EXPECT_EQ(p[2], 3.);

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "(x: 1, y: 2, z: 3)");

  EXPECT_TRUE(Vector3::kUnitX == Vector3(1., 0., 0));
  EXPECT_TRUE(Vector3::kUnitX != {1., 1., 0});
  EXPECT_TRUE(Vector3::kUnitY == {0., 1., 0});
  EXPECT_TRUE(Vector3::kUnitZ == Vector3::kUnitX.cross(Vector3::kUnitY));
  EXPECT_NEAR(Vector3::kUnitX.dot(Vector3::kUnitZ), 0., kTolerance);

  Vector3 t;
  EXPECT_EQ(t, Vector3::kZero);
  t.x() = 1.;
  t[1] = 2.;
  t.z() = 3.;
  EXPECT_EQ(t, p);
}

GTEST_TEST(Matrix3Test, Matrix3Operations) {
  const double kTolerance{1e-12};
  Matrix3 m1{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  const Matrix3 m2{1., 2., 3., 4., 5., 6., 7., 8., 9.};
  const Matrix3 m3 = Matrix3::kIdentity;

  EXPECT_EQ(m1, m2);
  EXPECT_EQ(m1 - m2, Matrix3::kZero);
  EXPECT_EQ(m1 + m2, m1 * 2.);
  EXPECT_EQ(m1 + m2, 2. * m2);
  EXPECT_EQ(m1 * m2, {1.,  4.,  9., 16., 25., 36., 49., 64., 81.});
  EXPECT_EQ(m1 / m2, Matrix3::kOnes);
  EXPECT_NEAR(m1.det(), 0., kTolerance);
  m1[2][2] = 10.;
  EXPECT_NEAR(m1.det(), -2.9999999999999996, kTolerance);

  std::stringstream ss;
  ss << m3;
  EXPECT_EQ(ss.str(), "[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");

  const std::vector<Vector3> kExpectedRows{Vector3(1., 2., 3.), Vector3(4., 5., 6.), Vector3(7., 8., 9.)};
  const std::vector<Vector3> kExpectedCols{Vector3(1., 4., 7.), Vector3(2., 5., 8.), Vector3(3., 6., 9.)};
  for (const Vector3& r : kExpectedRows) {
    bool found{false};
    for (int i = 0; i < 3; ++i) {
      if (r == m2.row(i)) {
        found = true;
        break;
      }
    }
    ASSERT_TRUE(found);
  }
  for (const Vector3& c : kExpectedCols) {
    bool found{false};
    for (int i = 0; i < 3; ++i) {
      if (c == m2.col(i)) {
        found = true;
        break;
      }
    }
    ASSERT_TRUE(found);
  }
}

GTEST_TEST(IsometryTest, IsometryOperations) {
  const double kTolerance{1e-12};
  const Isometry t1 = Isometry::FromTranslation({1., 2., 3.});
  const Isometry t2{{1., 2., 3.}, Matrix3::kIdentity};

  EXPECT_EQ(t1, t2);

  // This is not mathematically correct but it could be a nice to have.
  EXPECT_EQ(t1 * Vector3(1., 1., 1.), Vector3(2., 3., 4.));
  EXPECT_EQ(t1.transform({1., 1., 1.}), Vector3(2., 3., 4.));
  EXPECT_EQ(t1.inverse() * Vector3(2., 3., 4.), Vector3(1., 1., 1.));
  EXPECT_EQ(t1 * t2 * Vector3(1., 1., 1.), Vector3(3., 5., 7.));
  EXPECT_EQ(t1.compose(t2) * Vector3(1., 1., 1.), Vector3(3., 5., 7.));

  // Composes rotations.
  const Isometry t3{Isometry::RotateAround(Vector3::kUnitX, M_PI / 2.)};
  const Isometry t4{Isometry::RotateAround(Vector3::kUnitY, M_PI / 4.)};
  const Isometry t5{Isometry::RotateAround(Vector3::kUnitZ, M_PI / 8.)};
  const Isometry t6{Isometry::FromEulerAngles(M_PI / 2., M_PI / 4., M_PI / 8.)};
  // See https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#using-a-function-that-returns-an-assertionresult
  EXPECT_TRUE(areAlmostEqual(t6, t3 * t4 * t5, kTolerance));

  EXPECT_EQ(t3.translation(), Vector3::kZero);
  const double pi_8{M_PI / 8.};
  const double cpi_8{std::cos(pi_8)};  // 0.923879532
  const double spi_8{std::sin(pi_8)};  // 0.382683432
  EXPECT_TRUE(areAlmostEqual(t5.rotation(), Matrix3{cpi_8, -spi_8, 0., spi_8, cpi_8, 0., 0., 0., 1.}, kTolerance));

  std::stringstream ss;
  ss << t5;
  EXPECT_EQ(ss.str(), "[T: (x: 0, y: 0, z: 0), R:[[0.923879533, -0.382683432, 0], [0.382683432, 0.923879533, 0], [0, 0, 1]]]");
}

}  // namespace
}  // namespace test
}  // namespace math
}  // namespace ekumen

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
