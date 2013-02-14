#pragma once

#include <vector>
#include <string>

namespace FileUtils {

	class File
	{
	public:
		File(const std::string& filepath);
		std::string getFilename();
		std::string getfullPath();
		std::string getPath();
		bool isDirectory();

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
		Path(const std::vector<std::string>& pathLevels);
		std::string getValue();

		std::vector<std::string> levels;
	};
	
	const std::string file_separator = "\\";
	const std::string file_current_element = ".";
	const std::string file_back_element = "..";

	bool is_separator(const char& c);
	std::string get_current_directory();
	std::string get_filepath_only(const std::string& filename);
	std::string get_filename_only(const std::string& filename);
	std::vector<File> list_files(const std::string& root, bool recursive = false, const std::string& filter = "");
	std::string build_path(const std::string& path1, const std::string& path2);
	// TODO: static bool file_exists(const std::string& path);

}
