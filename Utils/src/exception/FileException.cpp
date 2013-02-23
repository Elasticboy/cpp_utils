#include "FileException.h"

FileException::FileException(const std::string& source, const std::string& message)
	: Exception("FileException", source, message)	{ }

OpenFileException::OpenFileException(const std::string& source, const std::string& message)
	: Exception("OpenFileException", source, message)	{ }

CloseFileException::CloseFileException(const std::string& source, const std::string& message)
	: Exception("CloseFileException", source, message)	{ }

ReadFileException::ReadFileException(const std::string& source, const std::string& message)
	: Exception("ReadFileException", source, message)	{ }

WriteFileException::WriteFileException(const std::string& source, const std::string& message)
	: Exception("WriteFileException", source, message)	{ }