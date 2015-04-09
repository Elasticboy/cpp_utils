#include <iostream>
#include <chrono>

#include "gtest/gtest.h"

TEST(TestTimer, ElapsedTime)
{
    ASSERT_FALSE(std::chrono::system_clock::is_steady) << "system_clock should not be steady.";
    ASSERT_FALSE(std::chrono::high_resolution_clock::is_steady) << "high_resolution_clock should not be steady.";
    ASSERT_TRUE(std::chrono::steady_clock::is_steady) << "steady_clock should be steady.";

    auto start = std::chrono::steady_clock::now();
    int i = 1000000;
    while (i > 0) { i--; }
    auto end = std::chrono::steady_clock::now();

    // Store the time difference between start and end
    auto diff = end - start;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    std::cout << std::chrono::duration<double, std::nano>(diff).count() << " ns" << std::endl;

    auto diff_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
    std::cout << diff_nano.count() << std::endl;

    SUCCEED();
}