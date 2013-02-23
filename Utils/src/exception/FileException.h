#pragma once

#include "Exception.h"

/*
 * File Exceptions classes
 */

class FileException : public Exception
{
public:
	FileException(const std::string& source, const std::string& message);
};

class OpenFileException : public Exception
{
public:
	OpenFileException(const std::string& source, const std::string& message);
};

class CloseFileException : public Exception
{
public:
	CloseFileException(const std::string& source, const std::string& message);
};

class ReadFileException : public Exception
{
public:
	ReadFileException(const std::string& source, const std::string& message);
};

class WriteFileException : public Exception
{
public:
	WriteFileException(const std::string& source, const std::string& message);
};