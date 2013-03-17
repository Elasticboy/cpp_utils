#include "CppUnitTest.h"
#include "..\Utils\src\fs_utils.h"
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fs_utils;
using namespace std;

namespace TestFileUtils
{
	TEST_CLASS(Test_Path)
	{
	public:
		
		/**
		* Tests the Build a Path from a string.
		*/
		TEST_METHOD(Test_Path_from_string)
		{
			const string pathAsString = "C:\\toto\\titi\\tata\\";
			Path pathFromString(pathAsString);
			
			const string expected	= pathAsString;
			const string actual		= pathFromString.getValue();

			Assert::AreEqual(expected, actual, L"PathAsString is not as expected.", LINE_INFO());
		}

		/**
		* Tests the Build a Path from a vector.
		*/
		TEST_METHOD(Test_Path_from_vector)
		{
			vector<string> pathLevels = vector<string>();
			pathLevels.push_back("C:");
			pathLevels.push_back("toto");
			pathLevels.push_back("titi");
			pathLevels.push_back("tata");
			Path pathFromLevel(pathLevels);

			const string expected	= "C:\\toto\\titi\\tata\\";
			const string actual		= pathFromLevel.getValue();

			Assert::AreEqual(expected, actual, L"pathFromLevel is not as expected.", LINE_INFO());
		}

		/**
		* Tests the Build a Path from a vector.
		*/
		TEST_METHOD(Test_get_current_path)
		{
			std::string path = get_current_directory();
			
			Assert::AreEqual(path, path, L"pathFromLevel is not as expected.", LINE_INFO());
		}

	};
}