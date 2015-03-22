#include "gtest/gtest.h"

#include <string>
#include <functional>
#include <regex>
#include <iostream>
#include <vector>

#include "../src/fs/fs_utils.h"
#include "../src/string_utils.h"

/**
		* List files with 1 argument :
		* - path
		*/
		TEST(TestFileUtils, ListFiles1Arg)
		{
			std::string root = "assets";
			const std::string fnameWinAPI = "assets";
			const std::string pathWinAPI = "assets";
			const std::string parentWinAPI = "assets";

			auto fileList		= fs_utils::list_files(root);
			ASSERT_TRUE(((int)fileList.size()) == 3) << "The sizes of the vectors are not equal.";

			const int size(fileList.size());
for (auto currentFile : fileList) {
				const std::string fname		= currentFile.filename();
				const std::string pathStr		= currentFile.path();
				const std::string parentBoost	= currentFile.parent_path();
				ASSERT_EQ(fname,	fnameWinAPI) << "Filenames do not match.";
				ASSERT_EQ(pathStr,		pathWinAPI) << "Pathes do not match.";
				ASSERT_EQ(parentBoost,	parentWinAPI) << "Filenames do not match.";
			}
		}

		/**
		* List files with 2 arguments :
		* - path
		* - recursive
		*/
		TEST(TestFileUtils, ListFiles2Args)
		{
std::string root = "assets";
			const bool recursive	= true;
const std::string fnameWinAPI = "assets";
const std::string pathWinAPI = "assets";
const std::string parentWinAPI = "assets";

			auto fileList		= fs_utils::list_files(root, recursive);
size_t fileCount = 3;
size_t realFileCount = fileList.size();

			ASSERT_EQ(realFileCount, fileCount) << "The sizes of the vectors are not equal.";

			const int size(fileList.size());
			for (auto currentFile : fileList) {
				auto fname		= currentFile.filename();
				const std::string pathStr		= currentFile.path();
				const std::string parentBoost	= currentFile.parent_path();
				ASSERT_EQ(fname,	fnameWinAPI) << "Filenames do not match.";
				ASSERT_EQ(pathStr,		pathWinAPI) << "Pathes do not match.";
				ASSERT_EQ(parentBoost,	parentWinAPI) << "Filenames do not match.";
			}
		}

		/**
		* List files with 3 arguments :
		* - path
		* - recursive
		* - filter
		*/
		TEST(TestFileUtils, ListFiles3Args)
		{
std::string root = "assets";
			const bool recursive	= true;
			const std::string filter		= ".*test.*";
size_t fileCount = 3;
const std::string fnameWinAPI = "assets";
const std::string pathWinAPI = "assets";
const std::string parentWinAPI = "assets";

			auto fileList		= fs_utils::list_files(root, recursive, filter);

			ASSERT_EQ(fileList.size(), fileCount) << "The sizes of the vectors are not equal.";

			const int size(fileList.size());
for (auto currentFile : fileList) {
				const std::string fname		= currentFile.filename();
				const std::string pathStr		= currentFile.path();
				const std::string parentBoost	= currentFile.parent_path();
				ASSERT_EQ(fname,	fnameWinAPI) << "Filenames do not match.";
				ASSERT_EQ(pathStr,		pathWinAPI) << "Pathes do not match.";
				ASSERT_EQ(parentBoost,	parentWinAPI) << "Filenames do not match.";
			}
		}

		/**
		* List files with 4 arguments :
		* - path
		* - recursive
		* - filter
		* - regularOnly
		*/
		TEST(TestFileUtils, ListFiles4Args)
		{
			std::string root = "assets";
			const bool recursive	= true;
			const std::string filter		= ".*test.*";
			const bool regularOnly	= true;
			const std::size_t fileCount = 3;
const std::string fnameWinAPI = "assets";
const std::string pathWinAPI = "assets";
const std::string parentWinAPI = "assets";

			auto fileList		= fs_utils::list_files(root, recursive, filter, regularOnly);

			ASSERT_EQ(fileList.size(), fileCount) << "The sizes of the vectors are not equal.";

			const int size(fileList.size());
for (auto currentFile : fileList) {
				const std::string fname		= currentFile.filename();
				const std::string pathStr		= currentFile.path();
				const std::string parentBoost	= currentFile.parent_path();
				ASSERT_EQ(fname,	fnameWinAPI) << "Filenames do not match.";
				ASSERT_EQ(pathStr,		pathWinAPI) << "Pathes do not match.";
				ASSERT_EQ(parentBoost,	parentWinAPI) << "Filenames do not match.";
			}
		}