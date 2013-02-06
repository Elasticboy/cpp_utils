#include "stdafx.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include <string>
#include <windows.h>

using namespace std;
namespace FileUtils {

	bool is_separator(const char& c)
	{
		return (c == '/') || (c == '\\');
	}

	/**
	* List the file of the directory passed as parameter.
	* @param directory The directory to explore.
	* @return A vector containing File objects.
	*/
	vector<File> list_files(const string& root, bool recursive, const string& filter)
	{
		
		// TODO: use file separator variable for this function
		// TODO: Clear "/" and "\" from root
		string clearedRoot = StringUtils::clear_right(root, is_separator);

		// Prepare string to use FindFile function
		// Add "\\*" to the end of the path.
		string searchPath = clearedRoot + "\\*";

		// Check wheather the path is longer than the maximum authorized size (MAX_PATH) 
		if (searchPath.length() > MAX_PATH) {
			throw exception("FileUtils::listFiles(), Path is too long.");
		}

		// Search for the first file of the directory.
		WIN32_FIND_DATAA fileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;

		hFind = FindFirstFileA(searchPath.c_str(), &fileData);
		if (hFind == INVALID_HANDLE_VALUE) {
			throw exception("FileUtils::listFiles(), Invalid handler value.");
		}

		// List all the files in the directory and get some informations
		LARGE_INTEGER filesize;
		auto fileList = vector<File>();

		do {
			File file;
			file.name = clearedRoot + "\\" + fileData.cFileName;

			// file size in bytes
			filesize.LowPart	= fileData.nFileSizeLow;
			filesize.HighPart	= fileData.nFileSizeHigh;
			file.size = filesize.QuadPart;

			// It is a directory
			if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

				// Skip directories ".", ".." and "$RECYCLE.BIN"
				if (strcmp(fileData.cFileName, ".") == 0 ||
					strcmp(fileData.cFileName, "..") == 0 ||
					strcmp(fileData.cFileName, "$RECYCLE.BIN") == 0 ) {
						continue;
				}
				file.type = File::TYPE_DIRECTORY;

				if (recursive) {
					// List the files in the directory
					auto directoryFiles = list_files(file.name, recursive, filter);
					// Add to the and of the current vector
					// TODO: check if insert is the better way to concatenate two vectors
					fileList.insert(fileList.end(), directoryFiles.begin(), directoryFiles.end());
				}

			} else { // If is a file
				file.type = File::TYPE_FILE;
			}
			fileList.push_back(file);

		} while (FindNextFileA(hFind, &fileData) != 0);

		auto error = GetLastError();
		if (error != ERROR_NO_MORE_FILES) {
			string msg = "FindNextFile error : " + to_string(error);
			throw exception(msg.c_str());
		}

		return fileList;
	}
}