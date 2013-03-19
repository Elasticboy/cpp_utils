#include "fs_utils.h"

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <regex>
#include <boost/filesystem.hpp>

#include "string_utils.h"
#include "exception/file_exception.h"

namespace fs_utils {

	using std::string;

	File::File(const string& filepath) : m_path(filepath) { }

	/**
	* @return The filename without the path.
	*/
	string File::filename()
	{
		return get_filename_only(m_path);
	}

	/**
	* @return the full path of the file (path and filename).
	*/
	string File::path()
	{
		return m_path;
	}

	/**
	* @return The path without the name.
	*/
	string File::parent_path()
	{
		return get_filepath_only(m_path);
	}

	/**
	* @return The size of the file.
	*/
	uintmax_t File::size()
	{
		if (is_regular_file()) {
			return boost::filesystem::file_size(boost::filesystem::path(m_path));
		}
		return uintmax_t(0);
	}

	/** @return True if the file is a directory. */
	bool File::is_directory()
	{
		return type == file_type::directory_file;
	}

	/** @return True if the file is a regular file. False otherwise. */
	bool File::is_regular_file()
	{
		return type == file_type::regular_file;
	}

	Path::Path(const std::string& path)
	{
		levels = std::vector<string>();
		string tempPath = path;

		while(!tempPath.empty()) {
			int nextSeparator = tempPath.find(file_separator);

			// Add the last remaining element.
			if (nextSeparator == string::npos) {
				levels.push_back(tempPath);
				break;
			}

			// Get first depth level of the temporary path and push it back to levels vector.
			if (nextSeparator != 0) {
				levels.push_back(tempPath.substr(0, nextSeparator));
			}

			// Remove element from the temporary path.
			tempPath = tempPath.substr(nextSeparator + 1, tempPath.size());
		}
	}

	Path::Path(const std::vector<string>& pathLevels)
	{
		levels = pathLevels;
	}

	string Path::getValue()
	{
		string value;
		for (auto level : levels) {
			value += level + file_separator;
		}
		return value;
	}

	bool is_separator(const char& c)
	{
		return (c == '/') || (c == '\\');
	}

	/**
	* @return the current directory.
	*/
	string get_current_directory() {
		try {
			return boost::filesystem::current_path().string();
		} catch (const boost::filesystem::filesystem_error& e) {
			throw file_exception("fs_utils::current_path", string(e.what()));
		}
	}

	/**
	* @return The path without the name of the file.
	*/
	string get_filepath_only(const string& filename)
	{
		int pos;

		if ((pos = filename.find_last_of('\\')) != string::npos) {
			return filename.substr(0, pos + 1);
		}

		if ((pos = filename.find_last_of('/')) != string::npos) {
			return filename.substr(0, pos + 1);
		}

		return "";
	}

	/**
	* @return The filename without the path.
	*/
	string get_filename_only(const string& filename)
	{
		int pos;

		if ((pos = filename.find_last_of('\\')) != string::npos) {
			return filename.substr(pos + 1);
		}

		if ((pos = filename.find_last_of('/')) != string::npos) {
			return filename.substr(pos + 1);
		}

		return filename;
	}

	/**
	* @return The filename without the extension.
	*/
	string trunc_extension(const string& filename)
	{
		int pos;

		if ((pos = filename.find_last_of('.')) != string::npos) {
			return filename.substr(0, pos);
		}

		return filename;
	}

	/**
	* List files and directories of the directory passed as parameter.
	* @param root The root directory to explore.
	* @param recursive True if the search should be recusive. False otherwise.
	* @param filter A string that will be turn into a regexp to select special files or directory.
	* @return A vector containing the File find by the function.
	*/
	std::vector<File> list_files(const string& root, bool recursive, const string& filter, bool regularFilesOnly)
	{
		namespace fs = boost::filesystem;
		// Error if root is like "C:" => "C:/"
		const string clearedRoot = string_utils::clear_right(root, is_separator) + fs_utils::file_separator;

		fs::path rootPath(clearedRoot);

		// Throw exception if path doesn't exist or isn't a directory.
		if (!fs::exists(rootPath)) {
			throw file_exception("fs_utils::list_files", "rootPath does not exist");
		}
		if (!fs::is_directory(rootPath)) {
			throw file_exception("fs_utils::list_files", "rootPath is not a directory.");
		}

		// List all the files in the directory and get some informations
		const std::regex regexFilter(filter);
		auto fileList = std::vector<File>();

		fs::directory_iterator end_itr;
		for( fs::directory_iterator it(rootPath); it != end_itr; ++it) {

			// TODO: REPLACE BY CORRECT FUNCTION !!!
			File file(it->path().string());

			// For a directory
			if (fs::is_directory(it->status())) {

				// Skip directories file_current_element and "$RECYCLE.BIN"
				if (it->path().filename() == file_current_element ||
					it->path().filename() == file_back_element ||
					it->path().filename() == "$Recycle.Bin" ||
					it->path().filename() == "$RECYCLE.BIN") {
						continue;
				}
				file.type = file_type::directory_file;

				if (recursive && it->path().string() != file_back_element) {
					// List the files in the directory
					auto directoryFiles = list_files(file.path(), recursive, filter, regularFilesOnly);
					// Add to the end of the current vector
					fileList.insert(fileList.end(), directoryFiles.begin(), directoryFiles.end());
				}

			} else if (fs::is_regular_file(it->status())) { // For a regular file
				if (filter != "" && !regex_match(file.path(), regexFilter)) {
					continue;
				}
				file.type = file_type::regular_file;

			} else {
				// TODO: throw an error
				file.type = file_type::unknown;
			}

			if (regularFilesOnly && !file.is_regular_file()) {
				continue;
			}

			// Add the file or directory to the list
			fileList.push_back(file);
		}

		return fileList;
	}

	/**
	* Concatenate two pathes and simplify the result.
	*/
	std::string build_path(const std::string& strPath1, const std::string& strPath2)
	{
		if (strPath2.find(':') != string::npos) {
			throw file_exception("fs_utils::build_path", "Second path can't contains ':' character.");
		}

		Path path1 = Path(strPath1);
		Path path2 = Path(strPath2);

		// Concatenate the two pathes
		auto concatenation = std::vector<string>();
		concatenation.insert(concatenation.end(), path1.levels.begin(), path1.levels.end());
		concatenation.insert(concatenation.end(), path2.levels.begin(), path2.levels.end());

		// Create the new path
		auto newPath = std::vector<string>();
		for (auto element : concatenation) {
			if (newPath.size() == 0) {
				newPath.push_back(element);
				continue;
			}

			const string lastAdded = newPath.back();
			if (element == file_back_element && !lastAdded.empty() && lastAdded != file_back_element) {
				newPath.pop_back();
				continue;
			}
			newPath.push_back(element);
		}

		path1.levels = newPath;

		return path1.getValue();
	}

	bool create_directory(const string& dirPath) {
		try {
			return boost::filesystem::create_directory(boost::filesystem::path(dirPath));
		} catch (const boost::filesystem::filesystem_error& e) {
			throw file_exception("fs_utils::create_directory", string(e.what()));
		}
	}
}
