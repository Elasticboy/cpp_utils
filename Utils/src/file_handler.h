#pragma once

#include <string>
#include <fstream>

namespace fh_open_mode {
    enum open_mode
	{
		read,
		write,
		append
	};
}

class file_handler
{
public:
	file_handler(const std::string& path, const fh_open_mode::open_mode& open_type);
	~file_handler();

	std::fstream& getFile();



private :
	std::fstream m_file;
	std::ios_base::openmode get_open_mode(const fh_open_mode::open_mode& open_mode);
};
