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
class OpenFileException		: public FileException { public: OpenFileException();	};
class CloseFileException	: public FileException { public: CloseFileException();	};
class ReadFileException		: public FileException { public: ReadFileException();	};
class WriteFileException	: public FileException { public: WriteFileException();	};