#pragma once

#include <vector>
#include <string>

class FileUtils
{
public:
	static std::vector<std::string> listFiles(const std::string& directory);
	// TODO: fileExists
};

