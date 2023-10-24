// test/test.cpp
#include <hello.hpp>
#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions)
{
    EXPECT_STRNE("hello", "world");
}