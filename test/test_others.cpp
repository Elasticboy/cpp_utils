#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include "../src/goemetry.h"
#include "../src/properties.h"
#include "../src/fs/fs_utils.h"

TEST(TestGeometry, TestPoint)
{
    auto pt = pointf();
    pt.display("pt");

    auto r = rect();
    r.display("rect");

    SUCCEED();

}

TEST(TestProp, Read)
{
    const std::string& currentDir = fs_utils::get_current_directory();
    const std::string propFile = fs_utils::build_path(currentDir, "../../blocks/cyrillrx/utils/test/assets/file1.txt");
    auto prop = properties(propFile);

    SUCCEED();
}