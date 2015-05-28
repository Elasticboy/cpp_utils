#include "file_handler.h"

#include "../exception/file_exception.h"

file_handler::file_handler(const std::string& path, const fh_open_mode::open_mode& open_mode)
{
    std::ios_base::openmode mode = get_open_mode(open_mode);

    try {
        file_.open(path.c_str(), mode);
    } catch (const std::exception& e) {
        throw open_file_exception("file_handler::file_handler",
                                  "Error while openning \"" + path + "\" : " + e.what() + ".");
    }

    if (!file_.is_open()) {
        throw open_file_exception("file_handler::file_handler", "File not found \"" + path + "\".");
    }
}

file_handler::~file_handler()
{
    if (file_.is_open()) {
        file_.close();
    }
}

std::fstream& file_handler::get_file()
{
    return file_;
}

/**
 * Get the ios_base::openmode corresponding to the internal open_mode value.
 * @param open_mode The mode of opening to translate.
 * @return The ios_base::openmode corresponding to the internal open_mode value.
 * @throws An open_file_exception if the given open_mode is not supported.
 */
std::ios_base::openmode file_handler::get_open_mode(const fh_open_mode::open_mode& open_mode)
{
    if (open_mode == fh_open_mode::read) {
        return std::ios_base::in;

    } else if (open_mode == fh_open_mode::write) {
        return std::ios_base::out;

    } else if (open_mode == fh_open_mode::append) {
        return std::ios_base::app;
    }

    throw open_file_exception("file_handler::get_open_mode()", "Openning mode \"" + std::to_string(open_mode) + "\" is not supported.");
}
