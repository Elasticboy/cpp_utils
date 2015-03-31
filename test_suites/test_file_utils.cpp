#include <string>
#include "gtest/gtest.h"
#include "../src/fs/fs_utils.h"

TEST(FileUtils, GetFilename)
{
    fs_utils::file file("C:\\toto\\titi\\tata\\bla.exe");

    const std::string expectedFilename = "bla.exe";
    auto actualFilename = file.filename();
    ASSERT_EQ(expectedFilename, actualFilename) << "Filename is not as expected.";
}

TEST(FileUtils, GetFilePath)
{
    fs_utils::file file("C:\\toto\\titi\\tata\\bla.exe");

    const std::string expectedFullPath = "C:\\toto\\titi\\tata\\bla.exe";
    auto actualFullPath = file.path();
    ASSERT_EQ(expectedFullPath, actualFullPath) << "FullPath is not as expected.";
}

TEST(FileUtils, GetParentPath)
{
    fs_utils::file file("C:\\toto\\titi\\tata\\bla.exe");

    const std::string expectedPath = "C:\\toto\\titi\\tata\\";
    auto actualPath = file.parent_path();
    ASSERT_EQ(expectedPath, actualPath) << "Path is not as expected.";
}