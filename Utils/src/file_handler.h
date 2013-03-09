#pragma once

#include <string>
#include <fstream>



class file_handler
{
public:
	file_handler(const std::string& path, const int& openType);
	~file_handler();

	std::fstream& getFile();

	static enum open_mode
	{ 
		read,
		write,
		append
	};

private :
	std::fstream m_file;
	std::ios_base::openmode getOpenMode(const int& openMode);
};