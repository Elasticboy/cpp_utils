#include <iostream>
#include "../src/logger.h"

#include "gtest/gtest.h"

TEST(TestLogger, Log)
{
    logger l("toto.txt");
    l.debug("Test message to log");
    SUCCEED();
}