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
	virtual const char* what() const throw();

protected:
	std::string m_message;
};

/*
 * Derived classes of PropertyException
 */
class LoadPropertyException : public PropertyException
{
public:
	LoadPropertyException(const std::string& message = "Error while loading property.");
};

class SavePropertyException : public PropertyException
{
public:
	SavePropertyException(const std::string& message = "Error while saving property.");
};

class ReadPropertyException : public PropertyException
{
public:
	ReadPropertyException(const std::string& message = "Error while reading property.");
};

class WritePropertyException : public PropertyException
{
public:
	WritePropertyException(const std::string& message = "Error while writing property.");
};