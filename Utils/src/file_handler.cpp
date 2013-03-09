#include "file_handler.h"

#include "exception\file_exception.h"

file_handler::file_handler(const std::string& path, const int& openMode)
{
	std::ios_base::openmode mode = getOpenMode(openMode);

	try {
		m_file.open(path.c_str(), mode);
	} catch (const std::exception& e) {
		throw open_file_exception("file_handler::file_handler", "Error while openning \"" + path + "\" : " + e.what() + ".");
	}

	if (!m_file.is_open()) {
		throw open_file_exception("file_handler::file_handler", "File not found \"" + path + "\".");
	}
}

file_handler::~file_handler()
{
	if (m_file.is_open()) {
		m_file.close();
	}
}

std::fstream& file_handler::getFile()
{
	return m_file;
}

/**
 * Get the ios_base::openmode corresponding to the internal openMode value.
 * @param openMode The mode of openning to translate.
 * @return The ios_base::openmode corresponding to the internal openMode value.
 * @throws An open_file_exception if the given openMode is not supported.
 */
std::ios_base::openmode file_handler::getOpenMode(const int& openMode)
{
	if (openMode == open_mode::read) {
		return std::ios_base::in;
		
	} else if (openMode == open_mode::write) {
		return std::ios_base::out;

	} else if (openMode == open_mode::append) {
		return std::ios_base::app;
	}
	
	throw open_file_exception("file_handler::getOpenMode()", "Openning mode \"" + std::to_string(openMode) + "\" is not supported.");
}