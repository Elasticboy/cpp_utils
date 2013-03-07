#include "CppUnitTest.h"
#include "..\Utils\src\fs_utils.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestFileUtils
{		
	TEST_CLASS(Test_File)
	{
	public:

		TEST_METHOD(Test_File_getFilename)
		{
			fs_utils::File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedFilename = "bla.exe";
			auto actualFilename	= file.getFilename();
			Assert::AreEqual(expectedFilename, actualFilename, L"Filename is not as expected.", LINE_INFO());
		}

		TEST_METHOD(Test_File_getfullPath)
		{
			fs_utils::File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedFullPath = "C:\\toto\\titi\\tata\\bla.exe";
			auto actualFullPath	= file.getfullPath(); 
			Assert::AreEqual(expectedFullPath, actualFullPath, L"FullPath is not as expected.", LINE_INFO());
		}

		TEST_METHOD(Test_File_getPath)
		{
			fs_utils::File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedPath = "C:\\toto\\titi\\tata\\";
			auto actualPath	= file.getPath(); 
			Assert::AreEqual(expectedPath, actualPath, L"Path is not as expected.", LINE_INFO());
		}

	};
}