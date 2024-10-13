#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "temp.h"

TEST(MathFunctionsTest, Addition) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(-1, -1), -2);
}

// Test case for subtraction
TEST(MathFunctionsTest, Subtraction) {
    EXPECT_EQ(subtract(5, 3), 2);
    EXPECT_EQ(subtract(0, 1), -1);
    EXPECT_EQ(subtract(-1, -1), 0);
}