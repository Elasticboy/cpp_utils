#include "CppUnitTest.h"

#include "..\Utils\src\FileUtils.h"
#include <string>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestFileUtils
{
	TEST_CLASS(Test_FileUtils_build_path)
	{
	public:

		/** Test concatenate Absolute + relative*/
		TEST_METHOD(Test_FileUtils_build_path1)
		{
			string path1 = "C:\\toto\\titi\\tata\\";
			string path2 = "..\\..\\";

			string expected	= "C:\\toto\\";
			string actual	= FileUtils::build_path(path1, path2); 

			Assert::AreEqual(expected, actual, L"", LINE_INFO());
		}

		/** Test concatenate relative + absolute */
		TEST_METHOD(Test_FileUtils_build_path2)
		{
			string path1 = "..\\..\\";
			string path2 = "C:\\toto\\titi\\tata\\";

			try {
				FileUtils::build_path(path1, path2);
				Assert::Fail(L"Should raise an exception.", LINE_INFO());

			} catch (const exception) {
				Assert::IsTrue(true, L"Exception occured as expected.");
			}
		}

		/** Test concatenate mixte */
		TEST_METHOD(Test_FileUtils_build_path3)
		{
			string path1 = "..\\toto\\..\\tata\\";
			string path2 = "..\\..\\";

			string expected	= "..\\..\\";
			string actual		= FileUtils::build_path(path1, path2); 

			Assert::AreEqual(expected, actual, L"", LINE_INFO());
		}

		/** Test concatenate relative + relative */
		TEST_METHOD(Test_FileUtils_build_path4)
		{
			string path1 = "..\\..\\..\\";
			string path2 = "..\\";

			string expected	= "..\\..\\..\\..\\";
			string actual		= FileUtils::build_path(path1, path2); 

			Assert::AreEqual(expected, actual, L"", LINE_INFO());
		}

		/** Test concatenate relative + relative */
		TEST_METHOD(Test_FileUtils_build_path5)
		{
			string path1 = "C:\\toto\\titi\\tata\\";
			string path2 = "D:\\tata\\titi\\toto\\";

			try {
				FileUtils::build_path(path1, path2);
				Assert::Fail(L"Should raise an exception.", LINE_INFO());

			} catch (const exception) {
				Assert::IsTrue(true, L"Exception occured as expected.");
			}
		}

	};
}