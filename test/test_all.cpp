#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include "../src/goemetry.h"
#include "../src/properties.h"
#include "../src/lang/lexicon_manager.h"
#include "../src/fs/fs_utils.h"

TEST(TestAll, Geometry)
{
    auto pt = pointf();
    pt.display("pt");

    auto r = rect();
    r.display("rect");

    SUCCEED();

}

TEST(TestAll, Properties)
{
    const std::string& currentDir = fs_utils::get_current_directory();
    const std::string& propFile = fs_utils::build_path(currentDir, "../../test/assets/file1.txt");
    auto prop = properties(propFile);

    SUCCEED();
}

TEST(TestAll, LexiconManager)
{
    auto manager = lexicon_manager::instance();
    manager->set_language(lexicon_manager::LANG_EN_US);

    SUCCEED();
}