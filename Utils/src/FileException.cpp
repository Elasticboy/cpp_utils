#include "stdafx.h"
#include "FileException.h"
#include <iostream>

FileException::FileException(std::string message) : m_Message(message)
{
	std::cerr << m_Message << std::endl;
}

OpenFileException::OpenFileException()
	: FileException("OpenFileException : Error while opening file.")	{ }

CloseFileException::CloseFileException()
	: FileException("CloseFileException : Error while closing file.")	{ }

ReadFileException::ReadFileException()
	: FileException("ReadFileException : Error while reading file.")	{ }

WriteFileException::WriteFileException()
	: FileException("WriteFileException : Error while writting file.")	{ }