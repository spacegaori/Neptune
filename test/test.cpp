// test/test.cpp
#include <neptune.hpp>
#include <gtest/gtest.h>

template <typename T>
class ConstructorTest : public testing::Test {
public:
    using value_type = T;

    using Array = std::array<value_type, 16>;
    using Vector = std::vector<value_type>;
    using Matrix = Neptune::Matrix<value_type>;
    using index_type = Matrix::index_type;

    using numeric_limits = std::numeric_limits<value_type>;
};

using NumericTypes = ::testing::Types<short, int, long int, long long int, float, double, long double>;
TYPED_TEST_SUITE(ConstructorTest, NumericTypes);
TYPED_TEST(ConstructorTest, DefaultValue)
{
    typename TestFixture::Matrix m{ 4, 4 };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    std::ranges::for_each(m, [](auto &e) { EXPECT_EQ(e, 0); });
}

TYPED_TEST(ConstructorTest, ZeroValue)
{
    typename TestFixture::Matrix m{ 4, 4, 0 };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    std::ranges::for_each(m, [](auto &e) { EXPECT_EQ(e, 0); });
}

TYPED_TEST(ConstructorTest, NegativeValue)
{
    typename TestFixture::Matrix m{ 4, 4, -1 };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    std::ranges::for_each(m, [](auto &e) { EXPECT_EQ(e, -1); });
}

TYPED_TEST(ConstructorTest, PositiveValue)
{
    typename TestFixture::Matrix m{ 4, 4, 1 };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    std::ranges::for_each(m, [](auto &e) { EXPECT_EQ(e, 1); });
}

TYPED_TEST(ConstructorTest, MinValue)
{
    auto min{ TestFixture::numeric_limits::min() };
    typename TestFixture::Matrix m{ 4, 4, min };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    std::ranges::for_each(m, [&min](auto &e) { EXPECT_EQ(e, min); });
}

TYPED_TEST(ConstructorTest, MaxValue)
{
    auto max{ TestFixture::numeric_limits::max() };
    typename TestFixture::Matrix m{ 4, 4, max };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    std::ranges::for_each(m, [&max](auto &e) { EXPECT_EQ(e, max); });
}

TYPED_TEST(ConstructorTest, InitList)
{
    auto min{ TestFixture::numeric_limits::min() };
    auto max{ TestFixture::numeric_limits::max() };
    typename TestFixture::Matrix m{ 4, 4, {
        0, -1, 1, min,
        max, 1, 0, -1, 
        1, 0, -1, max,
        -1, min, max, 1, } };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    auto m00{ m[0, 0] }; EXPECT_EQ(m00, 0);
    auto m01{ m[0, 1] }; EXPECT_EQ(m01, -1);
    auto m02{ m[0, 2] }; EXPECT_EQ(m02, 1);
    auto m03{ m[0, 3] }; EXPECT_EQ(m03, min);
    auto m10{ m[1, 0] }; EXPECT_EQ(m10, max);
    auto m11{ m[1, 1] }; EXPECT_EQ(m11, 1);
    auto m12{ m[1, 2] }; EXPECT_EQ(m12, 0);
    auto m13{ m[1, 3] }; EXPECT_EQ(m13, -1);
    auto m20{ m[2, 0] }; EXPECT_EQ(m20, 1);
    auto m21{ m[2, 1] }; EXPECT_EQ(m21, 0);
    auto m22{ m[2, 2] }; EXPECT_EQ(m22, -1);
    auto m23{ m[2, 3] }; EXPECT_EQ(m23, max);
    auto m30{ m[3, 0] }; EXPECT_EQ(m30, -1);
    auto m31{ m[3, 1] }; EXPECT_EQ(m31, min);
    auto m32{ m[3, 2] }; EXPECT_EQ(m32, max);
    auto m33{ m[3, 3] }; EXPECT_EQ(m33, 1);
}

TYPED_TEST(ConstructorTest, CArrayContainer)
{
    auto min{ TestFixture::numeric_limits::min() };
    auto max{ TestFixture::numeric_limits::max() };
    typename TestFixture::value_type a[16] {
        0, -1, 1, min,
        max, 1, 0, -1, 
        1, 0, -1, max,
        -1, min, max, 1 };
    typename TestFixture::Matrix m{ 4, 4, a };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    auto m00{ m[0, 0] }; EXPECT_EQ(m00, 0);
    auto m01{ m[0, 1] }; EXPECT_EQ(m01, -1);
    auto m02{ m[0, 2] }; EXPECT_EQ(m02, 1);
    auto m03{ m[0, 3] }; EXPECT_EQ(m03, min);
    auto m10{ m[1, 0] }; EXPECT_EQ(m10, max);
    auto m11{ m[1, 1] }; EXPECT_EQ(m11, 1);
    auto m12{ m[1, 2] }; EXPECT_EQ(m12, 0);
    auto m13{ m[1, 3] }; EXPECT_EQ(m13, -1);
    auto m20{ m[2, 0] }; EXPECT_EQ(m20, 1);
    auto m21{ m[2, 1] }; EXPECT_EQ(m21, 0);
    auto m22{ m[2, 2] }; EXPECT_EQ(m22, -1);
    auto m23{ m[2, 3] }; EXPECT_EQ(m23, max);
    auto m30{ m[3, 0] }; EXPECT_EQ(m30, -1);
    auto m31{ m[3, 1] }; EXPECT_EQ(m31, min);
    auto m32{ m[3, 2] }; EXPECT_EQ(m32, max);
    auto m33{ m[3, 3] }; EXPECT_EQ(m33, 1);
}

TYPED_TEST(ConstructorTest, ArrayContainer)
{
    auto min{ TestFixture::numeric_limits::min() };
    auto max{ TestFixture::numeric_limits::max() };
    typename TestFixture::Array a { {
        0, -1, 1, min,
        max, 1, 0, -1, 
        1, 0, -1, max,
        -1, min, max, 1 } };
    typename TestFixture::Matrix m{ 4, 4, a };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    auto m00{ m[0, 0] }; EXPECT_EQ(m00, 0);
    auto m01{ m[0, 1] }; EXPECT_EQ(m01, -1);
    auto m02{ m[0, 2] }; EXPECT_EQ(m02, 1);
    auto m03{ m[0, 3] }; EXPECT_EQ(m03, min);
    auto m10{ m[1, 0] }; EXPECT_EQ(m10, max);
    auto m11{ m[1, 1] }; EXPECT_EQ(m11, 1);
    auto m12{ m[1, 2] }; EXPECT_EQ(m12, 0);
    auto m13{ m[1, 3] }; EXPECT_EQ(m13, -1);
    auto m20{ m[2, 0] }; EXPECT_EQ(m20, 1);
    auto m21{ m[2, 1] }; EXPECT_EQ(m21, 0);
    auto m22{ m[2, 2] }; EXPECT_EQ(m22, -1);
    auto m23{ m[2, 3] }; EXPECT_EQ(m23, max);
    auto m30{ m[3, 0] }; EXPECT_EQ(m30, -1);
    auto m31{ m[3, 1] }; EXPECT_EQ(m31, min);
    auto m32{ m[3, 2] }; EXPECT_EQ(m32, max);
    auto m33{ m[3, 3] }; EXPECT_EQ(m33, 1);
}

TYPED_TEST(ConstructorTest, VectorContainer)
{
    auto min{ TestFixture::numeric_limits::min() };
    auto max{ TestFixture::numeric_limits::max() };
    typename TestFixture::Vector v{ { 
        0, -1, 1, min,
        max, 1, 0, -1, 
        1, 0, -1, max,
        -1, min, max, 1 } };
    typename TestFixture::Matrix m{ 4, 4, v };

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);
    auto m00{ m[0, 0] }; EXPECT_EQ(m00, 0);
    auto m01{ m[0, 1] }; EXPECT_EQ(m01, -1);
    auto m02{ m[0, 2] }; EXPECT_EQ(m02, 1);
    auto m03{ m[0, 3] }; EXPECT_EQ(m03, min);
    auto m10{ m[1, 0] }; EXPECT_EQ(m10, max);
    auto m11{ m[1, 1] }; EXPECT_EQ(m11, 1);
    auto m12{ m[1, 2] }; EXPECT_EQ(m12, 0);
    auto m13{ m[1, 3] }; EXPECT_EQ(m13, -1);
    auto m20{ m[2, 0] }; EXPECT_EQ(m20, 1);
    auto m21{ m[2, 1] }; EXPECT_EQ(m21, 0);
    auto m22{ m[2, 2] }; EXPECT_EQ(m22, -1);
    auto m23{ m[2, 3] }; EXPECT_EQ(m23, max);
    auto m30{ m[3, 0] }; EXPECT_EQ(m30, -1);
    auto m31{ m[3, 1] }; EXPECT_EQ(m31, min);
    auto m32{ m[3, 2] }; EXPECT_EQ(m32, max);
    auto m33{ m[3, 3] }; EXPECT_EQ(m33, 1);
}

// TODO: Test for copy constructors, move constructors, and the rest of the operations.