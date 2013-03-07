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

		TEST_METHOD(Test_File_filename)
		{
			fs_utils::File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedFilename = "bla.exe";
			auto actualFilename	= file.filename();
			Assert::AreEqual(expectedFilename, actualFilename, L"Filename is not as expected.", LINE_INFO());
		}

		TEST_METHOD(Test_File_path)
		{
			fs_utils::File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedFullPath = "C:\\toto\\titi\\tata\\bla.exe";
			auto actualFullPath	= file.path(); 
			Assert::AreEqual(expectedFullPath, actualFullPath, L"FullPath is not as expected.", LINE_INFO());
		}

		TEST_METHOD(Test_File_parent_path)
		{
			fs_utils::File file("C:\\toto\\titi\\tata\\bla.exe");

			const string expectedPath = "C:\\toto\\titi\\tata\\";
			auto actualPath	= file.parent_path(); 
			Assert::AreEqual(expectedPath, actualPath, L"Path is not as expected.", LINE_INFO());
		}

	};
}