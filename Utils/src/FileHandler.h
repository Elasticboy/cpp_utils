#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "FileException.h"

class FileHandler
{
public:
	FileHandler(const std::string& path, const int& openType);
	~FileHandler();
	
	std::fstream& getFile();

	static const int OPEN_MODE_READ		= 0;
	static const int OPEN_MODE_WRITE	= 1;
	static const int OPEN_MODE_APPEND	= 2;

private :
	std::fstream m_file;
	std::ios_base::openmode getOpenMode(const int& openMode);
};