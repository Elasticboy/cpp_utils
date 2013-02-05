#pragma once

#include <vector>
#include <string>

class File
{
public:
	static const int TYPE_DIRECTORY	= 0;
	static const int TYPE_FILE		= 1;

	std::string name;
	int type;
	long long size;
};

class FileUtils
{
public:
	static std::vector<File> listFiles(const std::string& directory);
	// TODO: fileExists
};

