#include "gtest/gtest.h"

#include <regex>

#include "../src/fs/fs_utils.h"

/**
* @return the path of assets directory
*/
std::string assets_dir()
{
    std::string currentDir = fs_utils::get_current_directory();
    return fs_utils::build_path(currentDir, "../../blocks/cyrillrx/utils/test_suites/assets");
}
/**
* List files with 1 argument :
* - path
*/
TEST(ListFiles, ListFiles1Arg)
{
    std::string root = assets_dir();
    auto fileList = fs_utils::list_files(root);

    ASSERT_EQ(fileList.size(), 6UL) << "Vector size should be 6.";

    int fileCount = 0;
    int dirCount = 0;

    for (auto currentFile : fileList) {
        if (currentFile.is_regular_file()) {
            fileCount++;
        }
        if (currentFile.is_directory()) {
            dirCount++;
        }
    }

    ASSERT_EQ(fileCount, 3) << "There should be 3 regular files.";
    ASSERT_EQ(dirCount, 3) << "There should be 3 directories.";
}

/**
* List files with 2 arguments :
* - path
* - recursive
*/
TEST(ListFiles, ListFiles2Args)
{
    std::string root = assets_dir();
    const bool recursive = true;
    auto fileList = fs_utils::list_files(root, recursive);

    ASSERT_EQ(fileList.size(), 23UL) << "Vector size should be 23.";

    int fileCount = 0;
    int dirCount = 0;

    for (auto currentFile : fileList) {
        if (currentFile.is_regular_file()) {
            fileCount++;
        }
        if (currentFile.is_directory()) {
            dirCount++;
        }
    }

    ASSERT_EQ(fileCount, 18) << "There should be 18 regular files.";
    ASSERT_EQ(dirCount, 5) << "There should be 5 directories.";
}

/**
* List files with 3 arguments :
* - path
* - recursive
* - filter
*/
TEST(ListFiles, ListFiles3Args)
{
    std::string root = assets_dir();
    const bool recursive = true;
    const std::string filter = ".*dirLevel2.*";
    auto fileList = fs_utils::list_files(root, recursive, filter);
    ASSERT_EQ(fileList.size(), 8UL) << "Vector size should be 8.";

    int fileCount = 0;
    int dirCount = 0;

    for (auto currentFile : fileList) {
        if (currentFile.is_regular_file()) {
            fileCount++;
        }
        if (currentFile.is_directory()) {
            dirCount++;
        }
    }

    ASSERT_EQ(fileCount, 6) << "There should be 6 regular files.";
    ASSERT_EQ(dirCount, 2) << "There should be 2 directories.";
}

/**
* List files with 4 arguments :
* - path
* - recursive
* - filter
* - regularOnly
*/
TEST(ListFiles, ListFiles4Args)
{
    std::string root = assets_dir();

    const bool recursive = true;
    const std::string filter = ".*dirLevel2_2.*";
    const bool regularOnly = true;
    auto fileList = fs_utils::list_files(root, recursive, filter, regularOnly);

    ASSERT_EQ(fileList.size(), 3UL) << "Vector size should be 3.";

    int fileCount = 0;
    int dirCount = 0;

    for (auto currentFile : fileList) {
        if (currentFile.is_regular_file()) {
            fileCount++;
        }
        if (currentFile.is_directory()) {
            dirCount++;
        }
    }

    ASSERT_EQ(fileCount, 3) << "There should be 18 regular files.";
    ASSERT_EQ(dirCount, 0) << "There should be no directory.";
}