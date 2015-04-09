#include "gtest/gtest.h"

#include "../src/fs/fs_utils.h"

/** Test concatenate Absolute + relative*/
TEST(BuildPath, Absolute_Relative)
{
    std::string path1 = "C:/toto/titi/tata/";
    std::string path2 = "../../";

    std::string expected = "C:/toto/";
    std::string actual = fs_utils::build_path(path1, path2);

    EXPECT_EQ(expected, actual);
}

/** Test concatenate relative + absolute */
TEST(BuildPath, Relative_Absolute)
{
    std::string path1 = "../../";
    std::string path2 = "C:/toto/titi/tata/";

    try {
        fs_utils::build_path(path1, path2);
        FAIL() << "Should raise an exception.";
    } catch (const std::exception) {
        ASSERT_TRUE(true) << "Exception occured as expected.";
    }
}

/** Test concatenate mix */
TEST(BuildPath, MixRelative_relative)
{
    std::string path1 = "../toto/../tata/";
    std::string path2 = "../../";

    std::string expected = "../../";
    std::string actual = fs_utils::build_path(path1, path2);

    EXPECT_EQ(expected, actual);
}

/** Test concatenate relative + relative */
TEST(BuildPath, Relative_Relative)
{
    std::string path1 = "../../../";
    std::string path2 = "../";

    std::string expected = "../../../../";
    std::string actual = fs_utils::build_path(path1, path2);

    EXPECT_EQ(expected, actual);
}

/** Test concatenate absolute + absolute */
TEST(BuildPath, Absolute_Absolute)
{
    std::string path1 = "C:/toto/titi/tata/";
    std::string path2 = "D:/tata/titi/toto/";

    try {
        fs_utils::build_path(path1, path2);
        FAIL() << "Should raise an exception.";

    } catch (const std::exception) {
        ASSERT_TRUE(true) << "Exception occured as expected.";
    }
}