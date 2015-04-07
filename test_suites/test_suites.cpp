#include "gtest/gtest.h"

// Tests utils
int main(int argc, char **argv)
{
    printf("Running utils test suite\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}