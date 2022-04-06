#include <iostream>
#include "../Fraction/Fraction.cpp"
#include "gtest/gtest.h"

TEST(FractionsTest, Construction) {
    EXPECT_EQ(Fraction(), Fraction(0, 1));
    EXPECT_EQ(Fraction(2, 4), Fraction(1, 2));
    EXPECT_EQ(Fraction(-1, -3), Fraction(1, 3));
    EXPECT_EQ(Fraction(1, -4), Fraction(-1, 4));
    EXPECT_EQ(Fraction(13, -26), Fraction(-1, 2));
    EXPECT_THROW(Fraction(0, 0), std::invalid_argument);
}

TEST (FractionsTest, MathOperations) {
    EXPECT_EQ(Fraction(1, 2) + Fraction(1, 2), Fraction(1, 1));
    EXPECT_EQ(Fraction(-2, 3) + Fraction(1, 2), Fraction(-1, 6));
    EXPECT_EQ(Fraction(1, 3) - Fraction(1, 3), Fraction(0, 1));
    EXPECT_EQ(Fraction(1, 3) * Fraction(-3, 1), Fraction(-1, 1));
    EXPECT_EQ(Fraction(1, 2) + Fraction(1, 3) / Fraction(1, 3), Fraction(3, 2));
}

TEST (FractionsTest, BoolOperations) {
    EXPECT_EQ(Fraction(1, 2) > 1, false);
    EXPECT_EQ(Fraction(0, 3) == Fraction(0, 1), true);
    EXPECT_EQ(Fraction(1, 3) < 0, false);
    EXPECT_EQ(1 == Fraction(-3, 1), false);
    EXPECT_EQ(Fraction(1, 3) / Fraction(1, 3) >= 0, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}