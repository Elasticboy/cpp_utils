#include "FileHandler.h"

#include "exception\FileException.h"

using namespace std;

FileHandler::FileHandler(const string& path, const int& openMode)
{
	ios_base::openmode mode = getOpenMode(openMode);

	try {
		m_file.open(path.c_str(), mode);
	} catch (const exception& e) {
		throw OpenFileException("FileHandler::FileHandler", "Error while openning \"" + path + "\" : " + e.what() + ".");
	}

	if (!m_file.is_open()) {
		throw OpenFileException("FileHandler::FileHandler", "File not found \"" + path + "\".");
	}
}

FileHandler::~FileHandler()
{
	if (m_file.is_open()) {
		m_file.close();
	}
}

fstream& FileHandler::getFile()
{
	return m_file;
}

/**
 * Get the ios_base::openmode corresponding to the internal openMode value.
 * @param openMode The mode of openning to translate.
 * @return The ios_base::openmode corresponding to the internal openMode value.
 * @throws An OpenFileException if the given openMode is not supported.
 */
ios_base::openmode FileHandler::getOpenMode(const int& openMode)
{
	if (openMode == OPEN_MODE_READ) {
		return ios_base::in;
		
	} else if (openMode == OPEN_MODE_WRITE) {
		return ios_base::out;

	} else if (openMode == OPEN_MODE_APPEND) {
		return ios_base::app;
	}
	
	throw OpenFileException("FileHandler::getOpenMode()", "Openning mode \"" + to_string(openMode) + "\" is not supported.");
}