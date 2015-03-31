#include <regex>
#include "gtest/gtest.h"
#include "../src/string_utils.h"

TEST(TestStringUtils, Test_regex_todo)
{
    std::regex r(".*(//|\\*|/\\*)+.*TODO.*");
    std::string str1 = "qsdqs /* sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str2 = "/* sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str3 = "qsd q * TODO sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str4 = "* TODO sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str5 = "qsd q // TODO sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str6 = "// TODO sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str7 = "sldkjfsmlkfj mslkdjf bla bla";
    std::string str8 = "qsdq sldkjfsmlkfj mslkdjf TODO bla bla";

    ASSERT_TRUE(regex_match(str1, r)) << "Regex should match.";
    ASSERT_TRUE(regex_match(str2, r)) << "Regex should match.";
    ASSERT_TRUE(regex_match(str3, r)) << "Regex should match.";
    ASSERT_TRUE(regex_match(str4, r)) << "Regex should match.";
    ASSERT_TRUE(regex_match(str5, r)) << "Regex should match.";
    ASSERT_TRUE(regex_match(str6, r)) << "Regex should match.";

    ASSERT_FALSE(regex_match(str7, r)) << "Regex should NOT match.";
    ASSERT_FALSE(regex_match(str8, r)) << "Regex should NOT match.";
}

TEST(TestStringUtils, Test_regex_extension)
{
    std::regex r(".*(\\.lang)");
    std::string str1 = "en.lang";
    std::string str2 = "toto/en.lang";
    std::string str3 = "toto/en.lang";
    std::string str4 = "toto/en.langqs";
    std::string str5 = "toto/lang/hello";
    std::string str6 = "lang/..";

    ASSERT_TRUE(regex_match(str1, r)) << "Regex should match.";
    ASSERT_TRUE(regex_match(str2, r)) << "Regex should match.";
    ASSERT_TRUE(regex_match(str3, r)) << "Regex should match.";

    ASSERT_FALSE(regex_match(str4, r)) << "Regex should NOT match.";
    ASSERT_FALSE(regex_match(str5, r)) << "Regex should NOT match.";
    ASSERT_FALSE(regex_match(str6, r)) << "Regex should NOT match.";
}

TEST(TestStringUtils, Trim)
{

    std::string input = "       bla, bla, bla     ";
    std::string expected = "bla, bla, bla";
    ASSERT_EQ(string_utils::trim(input), expected) << "String not trimmed as expected.";
}