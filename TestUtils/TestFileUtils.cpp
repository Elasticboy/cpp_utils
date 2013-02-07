#include "CppUnitTest.h"

#include "..\Utils\src\FileUtils.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestUtils
{		
	TEST_CLASS(TestFileUtils)
	{
	public:
		
		TEST_METHOD(FileUtils_build_path1)
		{
			std::string path1 = "C:\\toto\\titi\\tata\\";
			std::string path2 = "..\\..\\";

			std::string expected	= "C:\\toto\\";
			std::string actual		= FileUtils::build_path(path1, path2); 

			Assert::AreEqual(expected, actual, L"message", LINE_INFO());
		}

		TEST_METHOD(FileUtils_build_path2)
		{
			std::string path1 = "C:\\toto\\titi\\tata\\";
			std::string path2 = "\\..\\..\\";

			std::string expected	= "C:\\toto\\";
			std::string actual		= FileUtils::build_path(path1, path2); 

			Assert::AreEqual(expected, actual, L"message", LINE_INFO());
		}

		TEST_METHOD(FileUtils_build_path3)
		{
			std::string path1 = "..\\toto\\..\\tata\\";
			std::string path2 = "\\..\\..\\";

			std::string expected	= "..\\toto\\";
			std::string actual		= FileUtils::build_path(path1, path2); 

			Assert::AreEqual(expected, actual, L"message", LINE_INFO());
		}

	};
}