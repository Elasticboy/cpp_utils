#pragma once

#include <string>
#include <exception>

/**
 * Mother class for file exceptions.
 */
class FileException : public std::exception
{
public:
	FileException(std::string message) throw();
	virtual const char* what() const throw();

protected:
	std::string m_message;
};

/*
 * Derived classes of FileException
 */
class OpenFileException : public FileException
{
public:
	OpenFileException(const std::string& message = "Error while opening file.");
};

class CloseFileException : public FileException
{
public:
	CloseFileException(const std::string& message = "Error while closing file.");
};

class ReadFileException : public FileException
{
public:
	ReadFileException(const std::string& message = "Error while reading file.");
};

class WriteFileException : public FileException
{
public:
	WriteFileException(const std::string& message = "Error while writting file.");
};