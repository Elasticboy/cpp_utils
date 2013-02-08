#include "CppUnitTest.h"
#include "..\Utils\src\FileUtils.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestFileUtils
{		
	TEST_CLASS(Test_File)
	{
	public:
		/** Test concatenate Absolute + relative*/
		TEST_METHOD(TestFile_getFilename)
		{
			string path1 = "C:\\toto\\titi\\tata\\";
			string path2 = "..\\..\\";

			string expected	= "C:\\toto\\";
			string actual		= FileUtils::build_path(path1, path2); 

			Assert::AreEqual(expected, actual, L"", LINE_INFO());
		}

	};
}