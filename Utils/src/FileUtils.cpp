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

	string current_path() {

		char path[MAX_PATH];
		if (GetCurrentDirectoryA(MAX_PATH, path)) {
			return path;
		}

		throw exception("current_path(), Could'nt find the current path.");
	}

	/**
	* List the file of the directory passed as parameter.
	* @param directory The directory to explore.
	* @return A vector containing File objects.
	*/
	vector<File> list_files(const string& root, bool recursive, const string& filter)
	{
		string clearedRoot = StringUtils::clear_right(root, is_separator) + file_separator;

		// Prepare string to use FindFile function
		// Add "\\*" to the end of the path.
		const string searchPath = clearedRoot + "*";

		// Check wheather the path is longer than thea maximum authorized size (MAX_PATH) 
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
			file.name = current_path() + file_separator + clearedRoot + fileData.cFileName;

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
	
	/**
	* Concatenate two pathes
	*//*
	std::string build_path(const std::string& path1, const std::string& path2)
	{
		if (path2.find(':') != string::npos) {
			throw exception("Second path can't contains ':' character.");
		}

		string finalPath = path1;
		while (StringUtils::starts_with ..\\)
			remove(path2, ..\);
		
		if (path1 < )
			remove (path1,..\\)

		return finalPath;

	}
	*/
}