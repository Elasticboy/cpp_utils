#include "CppUnitTest.h"

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_NO_DEPRECATED
#endif

#include "..\Utils\src\fs_utils.h"
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

		/**
		* List files with 1 argument :
		* - path
		*/
		TEST_METHOD(Test_FileUtils_list_files1)
		{
			const string root = "C:/DevSpaces/VSProjects/CppUtils/TestFileUtils/test";

			// TODO: Record elapsed time
			auto filesWinAPI	= fs_utils::list_files_old(root); 
			auto filesBoost		= fs_utils::list_files(root);
			
			Assert::AreEqual(filesWinAPI.size(), filesBoost.size(), L"The sizes of the vectors are not equal.", LINE_INFO());
			
			const int size(filesBoost.size());
			for (int i = 0; i < size; i++) {
				Assert::AreEqual(filesBoost[i].filename(), filesWinAPI[i].filename(), L"Filenames do not match.", LINE_INFO());
			}
		}

		/**
		* List files with 2 arguments :
		* - path
		* - recursive
		*/
		TEST_METHOD(Test_FileUtils_list_files2)
		{
			const string root		= "C:/DevSpaces/VSProjects/CppUtils/TestFileUtils/test";
			const bool recursive	= true;

			// TODO: Record elapsed time
			auto filesWinAPI	= fs_utils::list_files_old(root, recursive); 
			auto filesBoost		= fs_utils::list_files(root, recursive);
			
			Assert::AreEqual(filesWinAPI.size(), filesBoost.size(), L"The sizes of the vectors are not equal.", LINE_INFO());
			
			const int size(filesBoost.size());
			for (int i = 0; i < size; i++) {
				Assert::AreEqual(filesBoost[i].filename(), filesWinAPI[i].filename(), L"Filenames do not match.", LINE_INFO());
			}
		}
		
		/**
		* List files with 3 arguments :
		* - path
		* - recursive
		* - filter
		*/
		TEST_METHOD(Test_FileUtils_list_files3)
		{
			const string root		= "C:/DevSpaces/VSProjects/CppUtils/TestFileUtils/test";
			const bool recursive	= true;
			const string filter		= ".*test.*";

			// TODO: Record elapsed time
			auto filesWinAPI	= fs_utils::list_files_old(root, recursive, filter); 
			auto filesBoost		= fs_utils::list_files(root, recursive, filter);
			
			Assert::AreEqual(filesWinAPI.size(), filesBoost.size(), L"The sizes of the vectors are not equal.", LINE_INFO());
			
			const int size(filesBoost.size());
			for (int i = 0; i < size; i++) {
				Assert::AreEqual(filesBoost[i].filename(), filesWinAPI[i].filename(), L"Filenames do not match.", LINE_INFO());
			}
		}
		
		/**
		* List files with 4 arguments :
		* - path
		* - recursive
		* - filter
		* - regularOnly
		*/
		TEST_METHOD(Test_FileUtils_list_files4)
		{
			const string root		= "C:/DevSpaces/VSProjects/CppUtils/TestFileUtils/test";
			const bool recursive	= true;
			const string filter		= ".*test.*";
			const bool regularOnly	= true;

			// TODO: Record elapsed time
			auto filesWinAPI	= fs_utils::list_files_old(root, recursive, filter, regularOnly); 
			auto filesBoost		= fs_utils::list_files(root, recursive, filter, regularOnly);
			
			Assert::AreEqual(filesWinAPI.size(), filesBoost.size(), L"The sizes of the vectors are not equal.", LINE_INFO());
			
			const int size(filesBoost.size());
			for (int i = 0; i < size; i++) {
				Assert::AreEqual(filesBoost[i].filename(), filesWinAPI[i].filename(), L"Filenames do not match.", LINE_INFO());
			}
		}
	};
}