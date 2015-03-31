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
    std::cout << "Search in dir : " << root << std::endl;

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

    ASSERT_EQ(fileCount, 3) << "There are 3 regular files.";
    ASSERT_EQ(dirCount, 3) << "There are 3 directories.";
}

/**
* List files with 2 arguments :
* - path
* - recursive
*/
TEST(ListFiles, ListFiles2Args)
{
    std::string root = assets_dir();
    std::cout << "Search in dir : " << root << std::endl;

    const bool recursive = true;
    const std::string fnameWinAPI = "assets";
    const std::string pathWinAPI = "assets";
    const std::string parentWinAPI = "assets";

    auto fileList = fs_utils::list_files(root, recursive);
    size_t fileCount = 3;
    size_t realFileCount = fileList.size();

    ASSERT_EQ(realFileCount, fileCount) << "The sizes of the vectors are not equal.";

    const int size(fileList.size());
    for (auto currentFile : fileList) {
        auto fname = currentFile.filename();
        const std::string pathStr = currentFile.path();
        const std::string parentBoost = currentFile.parent_path();
        ASSERT_EQ(fname, fnameWinAPI) << "Filenames do not match.";
        ASSERT_EQ(pathStr, pathWinAPI) << "Pathes do not match.";
        ASSERT_EQ(parentBoost, parentWinAPI) << "Filenames do not match.";
    }
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
    std::cout << "Search in dir : " << root << std::endl;

    const bool recursive = true;
    const std::string filter = ".*test.*";
    size_t fileCount = 3;
    const std::string fnameWinAPI = "assets";
    const std::string pathWinAPI = "assets";
    const std::string parentWinAPI = "assets";

    auto fileList = fs_utils::list_files(root, recursive, filter);

    ASSERT_EQ(fileList.size(), fileCount) << "The sizes of the vectors are not equal.";

    const int size(fileList.size());
    for (auto currentFile : fileList) {
        const std::string fname = currentFile.filename();
        const std::string pathStr = currentFile.path();
        const std::string parentBoost = currentFile.parent_path();
        ASSERT_EQ(fname, fnameWinAPI) << "Filenames do not match.";
        ASSERT_EQ(pathStr, pathWinAPI) << "Pathes do not match.";
        ASSERT_EQ(parentBoost, parentWinAPI) << "Filenames do not match.";
    }
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
    std::cout << "Search in dir : " << root << std::endl;

    const bool recursive = true;
    const std::string filter = ".*test.*";
    const bool regularOnly = true;
    const std::size_t fileCount = 3;
    const std::string fnameWinAPI = "assets";
    const std::string pathWinAPI = "assets";
    const std::string parentWinAPI = "assets";

    auto fileList = fs_utils::list_files(root, recursive, filter, regularOnly);

    ASSERT_EQ(fileList.size(), fileCount) << "The sizes of the vectors are not equal.";

    const int size(fileList.size());
    for (auto currentFile : fileList) {
        const std::string fname = currentFile.filename();
        const std::string pathStr = currentFile.path();
        const std::string parentBoost = currentFile.parent_path();
        ASSERT_EQ(fname, fnameWinAPI) << "Filenames do not match.";
        ASSERT_EQ(pathStr, pathWinAPI) << "Pathes do not match.";
        ASSERT_EQ(parentBoost, parentWinAPI) << "Filenames do not match.";
    }
}