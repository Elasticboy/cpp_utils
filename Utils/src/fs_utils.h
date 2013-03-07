#pragma once

#include <vector>
#include <string>

namespace fs_utils {

	enum file_type
	{ 
		regular_file,
		directory_file,
		unknown
	};

	class File
	{
	public:
		File(const std::string& filepath);
		std::string filename();
		std::string path();
		std::string parent_path();
		bool is_directory();
		bool is_regular_file();

		file_type type;
		long long size;

	private:
		std::string m_path;
	};

	class Path
	{
	public:
		Path(const std::string& path);
		Path(const std::vector<std::string>& pathLevels);
		std::string getValue();

		std::vector<std::string> levels;
	};

	const std::string file_separator		= "\\";
	const std::string file_current_element	= ".";
	const std::string file_back_element		= "..";

	bool is_separator(const char& c);
	std::string get_current_directory();
	std::string get_filepath_only(const std::string& filename);
	std::string get_filename_only(const std::string& filename);
	std::string trunc_extension(const std::string& filename);
	std::vector<File> list_files(const std::string& root, bool recursive = false, const std::string& filter = "", bool regularFilesOnly = false);
	// TODO: Clean deprecated
	std::vector<File> list_files_old(const std::string& root, bool recursive = false, const std::string& filter = "", bool regularFilesOnly = false);
	std::string build_path(const std::string& path1, const std::string& path2);
	// TODO: bool file_exists(const std::string& path);
	bool create_directory(const std::string& dirPath);
}
