#include "CppUnitTest.h"

#include "..\Utils\src\StringUtils.h"
#include <string>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestUtils
{
	TEST_CLASS(TestStringUtils)
	{
	public:

		TEST_METHOD(FileUtils_build_path1)
		{
			cout << "Simple search" << endl;
			vector<File> files = list_files(".\\");
			for (auto file : files) {
			cout << file.name << endl;
			}
			
			string path1 = current_path();
			string path2 = "..\\..\\";

			cout << "path1 : " << path1 << endl;
			cout << "path2 : " << path2 << endl;
			cout << "Concatenation " << build_path(path1, path2) << endl; 
			
			cout << "Recursive search" << endl;
			vector<File> filesRec = list_files(".\\", true);
			for (auto file : filesRec) {
			cout << file.name << endl;
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