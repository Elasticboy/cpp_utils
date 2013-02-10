#include "CppUnitTest.h"
#include "..\Utils\src\FileUtils.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FileUtils;
using namespace std;

namespace TestFileUtils
{		
	TEST_CLASS(Test_File)
	{
	public:

		TEST_METHOD(Test_File_getFilename)
		{
			File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedFilename = "bla.exe";
			const string actualFilename	= file.getFilename();
			Assert::AreEqual(expectedFilename, actualFilename, L"Filename is not as expected.", LINE_INFO());
		}

		TEST_METHOD(Test_File_getfullPath)
		{
			File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedFullPath = "C:\\toto\\titi\\tata\\bla.exe";
			const string actualFullPath	= file.getfullPath(); 
			Assert::AreEqual(expectedFullPath, actualFullPath, L"FullPath is not as expected.", LINE_INFO());
		}

		TEST_METHOD(Test_File_getPath)
		{
			File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedPath = "C:\\toto\\titi\\tata\\";
			const string actualPath	= file.getPath(); 
			Assert::AreEqual(expectedPath, actualPath, L"Path is not as expected.", LINE_INFO());
		}

	};
}