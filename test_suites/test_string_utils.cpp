#include <regex>
#include "gtest/gtest.h"
#include "../src/string_utils.h"
#include "../src/fs/fs_utils.h"

TEST(TestStringUtils, Test_regex_todo)
{
    std::regex r(".*(\\\\\\*|//|\\*).*TODO.*");
    std::string str1 = "qsdqs /* sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str2 = "/* sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str3 = "qsd q * TODO sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str4 = "* TODO sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str5 = "qsd q // TODO sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str6 = "// TODO sldkjfsmlkfj mslkdjf TODO bla bla";
    std::string str7 = "sldkjfsmlkfj mslkdjf bla bla";
    std::string str8 = "qsdq sldkjfsmlkfj mslkdjf TODO bla bla";

    ASSERT_TRUE(regex_search(str1, r)) << "Regex should match.";
    ASSERT_TRUE(regex_search(str2, r)) << "Regex should match.";
    ASSERT_TRUE(regex_search(str3, r)) << "Regex should match.";
    ASSERT_TRUE(regex_search(str4, r)) << "Regex should match.";
    ASSERT_TRUE(regex_search(str5, r)) << "Regex should match.";
    ASSERT_TRUE(regex_search(str6, r)) << "Regex should match.";
    ASSERT_FALSE(regex_search(str7, r)) << "Regex should NOT match.";
    ASSERT_FALSE(regex_search(str8, r)) << "Regex should NOT match.";
}

TEST(TestStringUtils, Test_regex_extension)
{
    std::regex r(".*(\\.lang)$");
    std::string str1 = "en.lang";
    std::string str2 = "toto\\en.lang";
    std::string str3 = "toto/en.lang";
    std::string str4 = "toto/en.langqs";
    std::string str5 = "toto\\lang\\hello";
    std::string str6 = "lang\\..";

    ASSERT_TRUE(regex_search(str1, r)) << "Regex should match.";
    ASSERT_TRUE(regex_search(str2, r)) << "Regex should match.";
    ASSERT_TRUE(regex_search(str3, r)) << "Regex should match.";

    ASSERT_FALSE(regex_search(str4, r)) << "Regex should NOT match.";
    ASSERT_FALSE(regex_search(str5, r)) << "Regex should NOT match.";
    ASSERT_FALSE(regex_search(str6, r)) << "Regex should NOT match.";
}

TEST(TestStringUtils, FileUtils_build_path1)
{
    std::cout << "Simple search" << std::endl;
    std::vector<fs_utils::file> files = fs_utils::list_files(".\\");
    for (auto file : files) {
        std::cout << file.path() << std::endl;
    }

    std::string path1 = fs_utils::get_current_directory();
    std::string path2 = "..\\..\\";

    std::cout << "path1 : " << path1 << std::endl;
    std::cout << "path2 : " << path2 << std::endl;
    std::cout << "Concatenation " << fs_utils::build_path(path1, path2) << std::endl;

    std::cout << "Recursive search" << std::endl;
    std::vector<fs_utils::file> filesRec = fs_utils::list_files(".\\", true);
    for (auto file : filesRec) {
        std::cout << file.path() << std::endl;
    }

    std::string str1 = "       bla, bla, bla     ";
    std::cout << "Before \"" << str1 << "\"" << std::endl;
    std::cout << "After  \"" << string_utils::trim(str1) << "\"" << std::endl;

    std::cout << std::endl;

    /*string str2 = "Mon fichier/bla/bla//";
    cout << "Before \"" << str2 << "\"" << endl;
    cout << "After  \"" << string_utils::clear_right(str2, is_separator) << "\"" << endl;

    cout << endl;

    string str3 = "Mon fichier\\bla\\bla\\";
    cout << "Before \"" << str3 << "\"" << endl;
    cout << "After  \"" << string_utils::clear_right(str3, is_separator) << "\"" << endl;*/
}