#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include "../src/geometry.h"

TEST(TestGeometry, TestPoint)
{
    auto pt = pointf();
    pt.display("pt");

    auto r = rect();
    r.display("rect");

    SUCCEED();
}