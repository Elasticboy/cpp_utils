#pragma once

#include <vector>
#include <string>

namespace FileUtils {

	class File
	{
	public:
		File(const std::string& filepath);
		std::string getFilename();
		std::string getFilepath();
		std::string getPath();

		static const int TYPE_DIRECTORY	= 0;
		static const int TYPE_FILE		= 1;
		int type;
		long long size;

	private:
		std::string m_filepath;

	};
	
	class Path
	{
	public:
		Path(const std::string& path);
		std::vector<std::string> levels;
		std::string getValue();
	};
	
	const std::string file_separator = "\\";
	const std::string file_current_element = ".";
	const std::string file_back_element = "..";

	bool is_separator(const char& c);
	std::string get_current_directory();
	std::vector<File> list_files(const std::string& root, bool recursive = false, const std::string& filter = "");
	std::string build_path(const std::string& path1, const std::string& path2);
	// TODO: static bool file_exists(const std::string& path);

}
