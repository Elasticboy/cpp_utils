#include "CppUnitTest.h"

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_NO_DEPRECATED
#endif

#include "..\Utils\src\FileUtils.h"
#include <string>
#include <functional>

#include <iostream>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestFileUtils
{
	TEST_CLASS(Test_FileUtils_list_files)
	{
	public:

		TEST_METHOD(Test_FileUtils_list_files1)
		{
			const string dir = FileUtils::get_current_directory();
			const string root = "C:\\DevSpaces\\VSProjects\\CppUtils\\TestFileUtils\\test";

			// TODO: Record elapsed time
			auto filesWinAPI	= FileUtils::list_files(root); 
			auto filesBoost		= FileUtils::list_files_boost(root);
			
			for (auto file : filesWinAPI) {
				cout << file.getfullPath() << endl;
			}

			cout << endl;

			for (auto file : filesBoost) {
				cout << file.getfullPath() << endl;
			}
			
			Assert::AreEqual(filesWinAPI.size(), filesBoost.size()+1, L"The sizes of the vectors are not equal.", LINE_INFO());

			for (int i = 0; i < filesBoost.size(); i++) {
				Assert::AreEqual(filesBoost[i].getFilename(), filesWinAPI[i+1].getFilename(), L"Filenames do not match.", LINE_INFO());
			}
		}
	};
}