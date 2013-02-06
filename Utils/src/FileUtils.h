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
	
	const std::string file_separator = "\\";
	bool is_separator(const char& c);
	std::string current_path();
	std::vector<File> list_files(const std::string& root, bool recursive = false, const std::string& filter = "");
	//std::string build_path(const std::string& path1, const std::string& path2);
	// TODO: static bool file_exists(const std::string& path);

}
