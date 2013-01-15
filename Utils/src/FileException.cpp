#include "stdafx.h"
#include "FileException.h"
#include <iostream>

FileException::FileException(std::string message)
	: m_message(message)
{
	std::cerr << m_message << std::endl;
}

const char* FileException::what() const throw()
{
	return m_message.c_str();
}

OpenFileException::OpenFileException(const std::string& message)
	: FileException("OpenFileException : "	+ message)	{ }

CloseFileException::CloseFileException(const std::string& message)
	: FileException("CloseFileException : "	+ message)	{ }

ReadFileException::ReadFileException(const std::string& message)
	: FileException("ReadFileException : "	+ message)	{ }

WriteFileException::WriteFileException(const std::string& message)
	: FileException("WriteFileException : "	+ message)	{ }