#pragma once

#include "Exception.h"

/*
 * File Exceptions classes
 */

class OpenFileException : public Exception
{
public:
	OpenFileException(const std::string& source, const std::string& message);// = "Error while opening file.");
};

class CloseFileException : public Exception
{
public:
	CloseFileException(const std::string& source, const std::string& message);// = "Error while closing file.");
};

class ReadFileException : public Exception
{
public:
	ReadFileException(const std::string& source, const std::string& message);// = "Error while reading file.");
};

class WriteFileException : public Exception
{
public:
	WriteFileException(const std::string& source, const std::string& message);// = "Error while writting file.");
};