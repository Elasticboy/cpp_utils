#include <string>
#include "gtest/gtest.h"
#include "../src/fs/fs_utils.h"

TEST(FileUtils, GetFilename)
{
    fs_utils::file file("C:/toto/titi/tata/bla.exe");

    const std::string expectedFilename = "bla.exe";
    auto actualFilename = file.filename();
    ASSERT_EQ(expectedFilename, actualFilename) << "Filename is not as expected.";
}

TEST(FileUtils, GetFilePath)
{
    fs_utils::file file("C:/toto/titi/tata/bla.exe");

    const std::string expectedFullPath = "C:/toto/titi/tata/bla.exe";
    auto actualFullPath = file.path();
    ASSERT_EQ(expectedFullPath, actualFullPath) << "FullPath is not as expected.";
}

TEST(FileUtils, GetParentPath)
{
    fs_utils::file file("C:/toto/titi/tata/bla.exe");

    const std::string expectedPath = "C:/toto/titi/tata/";
    auto actualPath = file.parent_path();
    ASSERT_EQ(expectedPath, actualPath) << "Path is not as expected.";
}

TEST(FileUtils, Exists)
{
    const std::string& currentDir = fs_utils::get_current_directory();

    const std::string fakeFile = fs_utils::build_path(currentDir, "../../blocks/cyrillrx/utils/test/assets/toto.txt");
    ASSERT_FALSE(fs_utils::exists(fakeFile)) << "Path should not exists.";

    const std::string existingDir = fs_utils::build_path(currentDir, "../../blocks/cyrillrx/utils/test/assets/dirLevel1_1");
    ASSERT_TRUE(fs_utils::exists(existingDir)) << "Directory does exist.";

    //const std::string existingFile = fs_utils::build_path(currentDir, "../../blocks/cyrillrx/utils/test/assets/file1.txt");
    //ASSERT_TRUE(fs_utils::exists(existingFile)) << "File does exist.";
}