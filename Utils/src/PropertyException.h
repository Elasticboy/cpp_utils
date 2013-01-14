#pragma once

#include <string>
#include <exception>

/**
 * Mother class for property exceptions.
 */
class PropertyException : public std::exception
{
public:
	PropertyException(const std::string& message) throw();
	PropertyException(const std::string& message, const std::string& subMessage) throw();
	virtual const char* what() const throw();

protected:
	std::string m_message;
	std::string m_subMessage;
};

/*
 * Derived classes of PropertyException
 */
class LoadPropertyException : public PropertyException
{
public:
	LoadPropertyException();
	LoadPropertyException(const std::string& message);
};

class SavePropertyException : public PropertyException
{
public:
	SavePropertyException();
	SavePropertyException(const std::string& message);
};

class ReadPropertyException : public PropertyException
{
public:
	ReadPropertyException();
	ReadPropertyException(const std::string& message);
};

class WritePropertyException : public PropertyException
{
public:
	WritePropertyException();
	WritePropertyException(const std::string& message);
};