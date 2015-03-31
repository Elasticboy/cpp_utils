#include "fs_utils.h"

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <regex>
#include <boost/filesystem.hpp>

#include "../string_utils.h"
#include "../exception/file_exception.h"

namespace fs_utils
{

    using std::string;

    file::file(const string &filePath) : path_(filePath) { }

    /**
    * @return The filename without the path.
    */
    string file::filename() const
    {
        return get_filename_only(path_);
    }

    /**
    * @return the full path of the file (path and filename).
    */
    string file::path() const
    {
        return path_;
    }

    /**
    * @return The path without the name.
    */
    string file::parent_path() const
    {
        return get_filepath_only(path_);
    }

    /**
    * @return The size of the file.
    */
    uintmax_t file::size() const
    {
        if (is_regular_file()) {
            return boost::filesystem::file_size(boost::filesystem::path(path_));
        }
        return uintmax_t(0);
    }

    /** @return True if the file is a directory. */
    bool file::is_directory() const
    {
        return type == file_type::directory_file;
    }

    /** @return True if the file is a regular file. False otherwise. */
    bool file::is_regular_file() const
    {
        return type == file_type::regular_file;
    }

    path::path(const std::string &path)
    {
        const bool startWithSeparator = path.find(file_separator) == 0;

        levels = std::vector<string>();
        string tempPath = path;

        while (!tempPath.empty()) {
            unsigned long nextSeparator = tempPath.find(file_separator);

            // Add the last remaining element.
            if (nextSeparator == string::npos) {
                levels.push_back(tempPath);
                break;
            }

            // Get first depth level of the temporary path and push it back to levels vector.
            if (nextSeparator != 0UL) {
                if (levels.empty() && startWithSeparator) {
                    // Keep leading separator for UNIX based OS
                    levels.push_back(std::string(1, file_separator) + tempPath.substr(0UL, nextSeparator));
                } else {
                    levels.push_back(tempPath.substr(0UL, nextSeparator));
                }

            }

            // Remove element from the temporary path.
            tempPath = tempPath.substr(nextSeparator + 1UL, tempPath.size());
        }
    }

    path::path(const std::vector<string> &path_levels)
    {
        levels = path_levels;
    }

    string path::to_string()
    {
        string path_as_string;
        for (auto level : levels) {
            path_as_string += level + file_separator;
        }
        return path_as_string;
    }

    bool is_separator(const char &c)
    {
        return (c == '/') || (c == '\\');
    }

    /**
    * @return the current directory.
    */
    string get_current_directory()
    {
        try {
            return boost::filesystem::current_path().string();
        } catch (const boost::filesystem::filesystem_error &e) {
            throw file_exception("fs_utils::current_path", string(e.what()));
        }
    }

    /**
    * @return The path without the name of the file.
    */
    string get_filepath_only(const string &filename)
    {
        int pos;

        if ((pos = filename.find_last_of('\\')) != string::npos) {
            return filename.substr(0, pos + 1UL);
        }

        if ((pos = filename.find_last_of('/')) != string::npos) {
            return filename.substr(0, pos + 1UL);
        }

        return "";
    }

    /**
    * @return The filename without the path.
    */
    string get_filename_only(const string &filename)
    {
        int pos;

        if ((pos = filename.find_last_of('\\')) != string::npos) {
            return filename.substr(pos + 1UL);
        }

        if ((pos = filename.find_last_of('/')) != string::npos) {
            return filename.substr(pos + 1UL);
        }

        return filename;
    }

    /**
    * @return The filename without the extension.
    */
    string trunc_extension(const string &filename)
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
    * @param recursive True if the search should be recursive. False otherwise.
    * @param filter A string that will be turn into a regexp to select special files or directory.
    * @return A vector containing the File find by the function.
    */
    std::vector<file> list_files(const string &root, bool recursive, const string &filter, bool regular_files_only)
    {
        namespace fs = boost::filesystem;
        // Error if root is like "C:" => "C:/"
        const string clearedRoot = string_utils::clear_right(root, is_separator) + file_separator;

        fs::path rootPath(clearedRoot);

        // Throw exception if path doesn't exist or isn't a directory.
        if (!fs::exists(rootPath)) {
            throw file_exception("fs_utils::list_files", "root \"" + root + "\" does not exist");
        }
        if (!fs::is_directory(rootPath)) {
            throw file_exception("fs_utils::list_files", "root \"" + root + "\" is not a directory.");
        }

        // List all the files in the directory and get some information
        const std::regex regexFilter(filter);
        auto fileList = std::vector<file>();

        fs::directory_iterator end_itr;
        for (fs::directory_iterator it(rootPath); it != end_itr; ++it) {

            // TODO: REPLACE BY CORRECT FUNCTION !!!
            file file(it->path().string());

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
                    auto directoryFiles = list_files(file.path(), recursive, filter, regular_files_only);
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

            if (regular_files_only && !file.is_regular_file()) {
                continue;
            }

            // Add the file or directory to the list
            fileList.push_back(file);
        }

        return fileList;
    }

    /**
    * Concatenate two paths and simplify the result.
    */
    std::string build_path(const std::string &path_as_string_1, const std::string &path_as_string_2)
    {
        if (path_as_string_2.find(':') != string::npos || path_as_string_2.find(file_separator) == 0) {
            throw file_exception("fs_utils::build_path", "Second path can't be absolute");
        }

        path path1 = path(path_as_string_1);
        path path2 = path(path_as_string_2);

        // Concatenate the two paths
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

        return path1.to_string();
    }

    bool create_directory(const string &dirPath)
    {
        try {
            return boost::filesystem::create_directory(boost::filesystem::path(dirPath));
        } catch (const boost::filesystem::filesystem_error &e) {
            throw file_exception("fs_utils::create_directory", string(e.what()));
        }
    }
}
