#include "CppUnitTest.h"

#include "..\Utils\src\StringUtils.h"
#include "..\Utils\src\fs_utils.h"
#include <string>
#include <iostream>
#include <vector>
#include <regex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fs_utils;
using namespace std;

namespace TestUtils
{
	TEST_CLASS(TestStringUtils)
	{
	public:

		TEST_METHOD(Test_regex_todo)
		{
			regex r(".*(\\\\\\*|//|\\*).*TODO.*");
			string str1 = "qsdqs /* sldkjfsmlkfj mslkdjf TODO bla bla";
			string str2 = "/* sldkjfsmlkfj mslkdjf TODO bla bla";
			string str3 = "qsd q * TODO sldkjfsmlkfj mslkdjf TODO bla bla";
			string str4 = "* TODO sldkjfsmlkfj mslkdjf TODO bla bla";
			string str5 = "qsd q // TODO sldkjfsmlkfj mslkdjf TODO bla bla";
			string str6 = "// TODO sldkjfsmlkfj mslkdjf TODO bla bla";
			string str7 = "sldkjfsmlkfj mslkdjf bla bla";
			string str8 = "qsdq sldkjfsmlkfj mslkdjf TODO bla bla";

			Assert::IsTrue(regex_search(str1, r), L"Regex should match.", LINE_INFO());
			Assert::IsTrue(regex_search(str2, r), L"Regex should match.", LINE_INFO());
			Assert::IsTrue(regex_search(str3, r), L"Regex should match.", LINE_INFO());
			Assert::IsTrue(regex_search(str4, r), L"Regex should match.", LINE_INFO());
			Assert::IsTrue(regex_search(str5, r), L"Regex should match.", LINE_INFO());
			Assert::IsTrue(regex_search(str6, r), L"Regex should match.", LINE_INFO());
			Assert::IsFalse(regex_search(str7, r), L"Regex should NOT match.", LINE_INFO());
			Assert::IsFalse(regex_search(str8, r), L"Regex should NOT match.", LINE_INFO());
		}
		
		TEST_METHOD(Test_regex_extension)
		{
			regex r(".*(\\.lang)$");
			string str1 = "en.lang";
			string str2 = "toto\\en.lang";
			string str3 = "toto/en.lang";
			
			string str4 = "toto/en.langqs";
			string str5 = "toto\\lang\\hello";
			string str6 = "lang\\..";

			Assert::IsTrue(regex_search(str1, r), L"Regex should match.", LINE_INFO());
			Assert::IsTrue(regex_search(str2, r), L"Regex should match.", LINE_INFO());
			Assert::IsTrue(regex_search(str3, r), L"Regex should match.", LINE_INFO());

			Assert::IsFalse(regex_search(str4, r), L"Regex should NOT match.", LINE_INFO());
			Assert::IsFalse(regex_search(str5, r), L"Regex should NOT match.", LINE_INFO());
			Assert::IsFalse(regex_search(str6, r), L"Regex should NOT match.", LINE_INFO());
		}

			TEST_METHOD(FileUtils_build_path1)
		{
			cout << "Simple search" << endl;
			vector<File> files = list_files(".\\");
			for (auto file : files) {
				cout << file.getfullPath() << endl;
			}

			string path1 = get_current_directory();
			string path2 = "..\\..\\";

			cout << "path1 : " << path1 << endl;
			cout << "path2 : " << path2 << endl;
			cout << "Concatenation " << build_path(path1, path2) << endl; 

			cout << "Recursive search" << endl;
			vector<File> filesRec = list_files(".\\", true);
			for (auto file : filesRec) {
				cout << file.getfullPath() << endl;
			}

			string str1 = "       bla, bla, bla     ";
			cout << "Before \"" << str1 << "\"" << endl;
			cout << "After  \"" << StringUtils::trim(str1) << "\"" << endl;

			cout << endl;

			string str2 = "Mon fichier/bla/bla//";
			cout << "Before \"" << str2 << "\"" << endl;
			cout << "After  \"" << StringUtils::clear_right(str2, is_separator) << "\"" << endl;

			cout << endl;

			string str3 = "Mon fichier\\bla\\bla\\";
			cout << "Before \"" << str3 << "\"" << endl;
			cout << "After  \"" << StringUtils::clear_right(str3, is_separator) << "\"" << endl;
		}

	};
}