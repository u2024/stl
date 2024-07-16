#include <vector>

#include "arithmeticAverage.hpp"
#include "gtest/gtest.h"

constexpr double epsilon = 0.001;

TEST(arithmeticAverageTest, ShouldCalculateArithmeticAverage) {
    std::vector<int> first{-5, 4, 2, -5, 2, 4, 6, 7};
    std::vector<int> second{3, 5, -2, 6, 7, -3, 6, 9};
    EXPECT_NEAR(ArithmeticAverage(first, second), 2.875, epsilon);
    
    first = {12, 14, 18, 20};
    second = {22, 24, 26, 30};
    double expected = 20.75;
    EXPECT_NEAR(ArithmeticAverage(first, second), expected, 0.00001);
    
    first = {3, 141, 1, 0, 2, 718281828};
    second = {1, 22000, -21432, 34567, -2, 123};
    expected = 59859769.333333;
    EXPECT_NEAR(ArithmeticAverage(first, second), expected, 0.00001);

    first = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    second = {1, 3, 9, 27, 81, 243, 729, 2187, 6561};
    expected = 575.111111111;
    EXPECT_NEAR(ArithmeticAverage(first, second), expected, 0.00001);

    first = {1, -1, 2, -2, 3, -3, 4, -4};
    second = {2, 3, 5, 7, 11, 13, 17, 19};
    expected = 4.8125;
    EXPECT_NEAR(ArithmeticAverage(first, second), expected, 0.00001);

    first = {4087, 1740, 5502, 7572, 7235};
    second = {4991, 3441, 5031, 4869, 5083};
    expected = 4955.1;
    EXPECT_NEAR(ArithmeticAverage(first, second), expected, 0.00001);    
}

TEST(arithmeticAverageTest, ShouldCalculateDistance) {
    std::vector<int> first{7, 4, 3};
    std::vector<int> second{17, 6, 2};
    double expected = 10.247;
    EXPECT_NEAR(Distance(first, second), expected, epsilon);

    first = {7, 4, 3, 13};
    second = {17, 6, 2, -2};
    expected = 18.16590212458495;
    EXPECT_NEAR(Distance(first, second), expected, 0.00001);

    first = {1, 2, 3, 4, 5};
    second = {-10, 0, -234567, 684, 11};
    expected = 234570.985974395;
    EXPECT_NEAR(Distance(first, second), expected, 0.00001);

    first = {-2, 2};
    second = {0, 1};
    expected = 2.236067977;
    EXPECT_NEAR(Distance(first, second), expected, 0.00001);

    first = {1, 5, 10};
    second = {0, 0, 0};
    expected = 11.22497216;
    EXPECT_NEAR(Distance(first, second), expected, 0.00001);

    first = {1, 4, 9, 16, 25, 36, 49};
    second = {3, 1, 4, 1, 5, 9, 2};
    expected = 60.008332755;
    EXPECT_NEAR(Distance(first, second), expected, 0.00001);    
}
