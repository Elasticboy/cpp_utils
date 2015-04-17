#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace fs_utils {

	enum file_type
	{
		regular_file,
		directory_file,
		unknown
	};

	class file
	{
	public:
		file(const std::string& filePath);
		std::string filename() const;
		std::string path() const;
		std::string parent_path() const;
		uintmax_t size() const;
		bool is_directory() const;
		bool is_regular_file() const;

		file_type type;

	private:
		std::string path_;
	};

	class path
	{
	public:
		path(const std::string& path);
		path(const std::vector<std::string>& path_levels);
		std::string to_string();

		std::vector<std::string> levels;
	};

	const char file_separator = '/';
	const std::string file_current_element	= ".";
	const std::string file_back_element		= "..";


	bool is_separator(const char& c);

	std::string get_current_directory();
	std::string get_filepath_only(const std::string& filename);
	std::string get_filename_only(const std::string& filename);
	std::string trunc_extension(const std::string& filename);
	std::vector<file> list_files(const std::string& root, bool recursive = false, const std::string& filter = "", bool regular_files_only = false);
	std::string build_path(const std::string& path1, const std::string& path2);
	bool exists(const std::string& path);
	bool create_directory(const std::string& dir_path);
}
