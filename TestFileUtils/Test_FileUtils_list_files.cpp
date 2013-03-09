#include "CppUnitTest.h"

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <string>
#include <functional>
#include <regex>
#include <iostream>
#include <vector>

#include "..\Utils\src\fs_utils.h"
#include "..\Utils\src\string_utils.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestFileUtils
{
	
	bool is_separator(const char& c)
	{
		return (c == '/') || (c == '\\');
	}

	TEST_CLASS(Test_FileUtils_list_files)
	{
	public:
		std::vector<fs_utils::File> list_files_old(std::string& root, bool recursive = false, const std::string& filter = "", bool regularFilesOnly = false);
		/**
		* List files with 1 argument :
		* - path
		*/
		TEST_METHOD(Test_FileUtils_list_files1)
		{
			string root = "C:/DevSpaces/VSProjects/CppUtils/TestFileUtils/test";

			// TODO: Record elapsed time
			auto filesWinAPI	= list_files_old(root); 
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
			string root		= "C:/DevSpaces/VSProjects/CppUtils/TestFileUtils/test";
			const bool recursive	= true;

			// TODO: Record elapsed time
			auto filesWinAPI	= list_files_old(root, recursive); 
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
			string root		= "C:/DevSpaces/VSProjects/CppUtils/TestFileUtils/test";
			const bool recursive	= true;
			const string filter		= ".*test.*";

			// TODO: Record elapsed time
			auto filesWinAPI	= list_files_old(root, recursive, filter); 
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
			string root		= "C:/DevSpaces/VSProjects/CppUtils/TestFileUtils/test";
			const bool recursive	= true;
			const string filter		= ".*test.*";
			const bool regularOnly	= true;

			// TODO: Record elapsed time
			auto filesWinAPI	= list_files_old(root, recursive, filter, regularOnly); 
			auto filesBoost		= fs_utils::list_files(root, recursive, filter, regularOnly);

			Assert::AreEqual(filesWinAPI.size(), filesBoost.size(), L"The sizes of the vectors are not equal.", LINE_INFO());

			const int size(filesBoost.size());
			for (int i = 0; i < size; i++) {
				Assert::AreEqual(filesBoost[i].filename(), filesWinAPI[i].filename(), L"Filenames do not match.", LINE_INFO());
			}
		}
	};

	/**
	* List files and directories of the directory passed as parameter.
	* @param root The root directory to explore.
	* @param recursive True if the search should be recusive. False otherwise.
	* @param filter A string that will be turn into a regexp to select special files or directory.
	* @return A vector containing the File find by the function.
	*/
	std::vector<fs_utils::File> Test_FileUtils_list_files::list_files_old(string& root, bool recursive, const string& filter, bool regularFilesOnly)
	{
		// TODO: Implement boost for the rest of the function.
		replace(root.begin(), root.end(), '/', '\\');
		string clearedRoot = string_utils::clear_right(root, is_separator) + fs_utils::file_separator;
		// TODO: get full path function if root is relative

		// Prepare string to use FindFile function
		// Add "\\*" to the end of the path.
		const string searchPath = clearedRoot + "*";

		// Check wheather the path is longer than the maximum authorized size (MAX_PATH) 
		if (searchPath.length() > MAX_PATH) {
			throw exception("list_files, Path is too long.");
		}

		// Search for the first file of the directory.
		WIN32_FIND_DATAA fileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;

		hFind = FindFirstFileA(searchPath.c_str(), &fileData);
		if (hFind == INVALID_HANDLE_VALUE) {
			throw exception("list_files, Invalid handler value.");
		}

		// List all the files in the directory and get some informations
		const std::regex regexFilter(filter);
		LARGE_INTEGER filesize;
		auto fileList = std::vector<fs_utils::File>();

		do {
			fs_utils::File file(clearedRoot + fileData.cFileName);

			// file size in bytes
			filesize.LowPart	= fileData.nFileSizeLow;
			filesize.HighPart	= fileData.nFileSizeHigh;
			//file.size = filesize.QuadPart;

			// It is a directory
			if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

				// Skip directories file_current_element and "$RECYCLE.BIN"
				if (strcmp(fileData.cFileName, fs_utils::file_current_element.c_str()) == 0 ||
					strcmp(fileData.cFileName, fs_utils::file_back_element.c_str()) == 0 ||
					strcmp(fileData.cFileName, "$Recycle.Bin") == 0 ||
					strcmp(fileData.cFileName, "$RECYCLE.BIN") == 0 ) {
						continue;
				}
				file.type = fs_utils::file_type::directory_file;

				if (recursive && strcmp(fileData.cFileName, fs_utils::file_back_element.c_str()) != 0) {
					// List the files in the directory
					auto directoryFiles = list_files_old(file.path(), recursive, filter, regularFilesOnly);
					// Add to the end of the current vector
					fileList.insert(fileList.end(), directoryFiles.begin(), directoryFiles.end());
				}

			} else { // If is a file
				if (filter != "" && !regex_match(file.path(), regexFilter)) {
					continue;
				}
				file.type = fs_utils::file_type::regular_file;
			}

			if (regularFilesOnly && !file.is_regular_file()) {
				continue;
			}

			// Add the file or directory to the list
			fileList.push_back(file);

		} while (FindNextFileA(hFind, &fileData) != 0);

		FindClose(hFind);

		auto error = GetLastError();
		if (error != ERROR_NO_MORE_FILES) {
			const string msg = "list_files, FindNextFile error : " + std::to_string(error);
			throw exception(msg.c_str());
		}
		return fileList;
	}
}