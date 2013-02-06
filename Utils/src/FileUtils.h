#pragma once

#include <vector>
#include <string>

namespace FileUtils {

	class File
	{
	public:
		static const int TYPE_DIRECTORY	= 0;
		static const int TYPE_FILE		= 1;

		std::string name;
		int type;
		long long size;
	};
	
	bool is_separator(const char& c);
	std::vector<File> list_files(const std::string& directory, bool recursive = false, const std::string& filter = "");
	// TODO: static bool file_exists(const std::string& path);

}
