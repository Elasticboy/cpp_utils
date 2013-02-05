#include "stdafx.h"
#include "FileUtils.h"
#include <string>
#include <windows.h>

using namespace std;

vector<File> FileUtils::listFiles(const string& directory)
{
	// Prepare string to use FindFile function
	// Add "\\*" to the end of the path.
	string searchPath = directory + "\\*";

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
	vector<File> fileList = vector<File>();
	
	do {
		File file;
		file.name = fileData.cFileName;
		
		// file size in bytes
		filesize.LowPart	= fileData.nFileSizeLow;
		filesize.HighPart	= fileData.nFileSizeHigh;
		file.size = filesize.QuadPart;

		// It is a directory
		if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			
			// Skip directories "." and "$RECYCLE.BIN"
			if (strcmp(fileData.cFileName, ".") == 0 || strcmp(fileData.cFileName, "$RECYCLE.BIN") == 0 ) {
				continue;
			}
			file.type = File::TYPE_DIRECTORY;

		} else { // If is a file
			file.type = File::TYPE_FILE;
		}
		fileList.push_back(file);

	} while (FindNextFileA(hFind, &fileData) != 0);
 
	DWORD dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) {
		string msg = "FindNextFile error : " + to_string(dwError);
		throw exception(msg.c_str());
	}

	return fileList;
}
