#pragma once

#include "Exception.h"

/*
 * Property Exceptions classes
 */

class LoadPropertyException : public Exception
{
public:
	LoadPropertyException(const std::string& source, const std::string& message);// = "Error while loading property.");
};

class SavePropertyException : public Exception
{
public:
	SavePropertyException(const std::string& source, const std::string& message);// = "Error while saving property.");
};

class ReadPropertyException : public Exception
{
public:
	ReadPropertyException(const std::string& source, const std::string& message);// = "Error while reading property.");
};

class WritePropertyException : public Exception
{
public:
	WritePropertyException(const std::string& source, const std::string& message);// = "Error while writing property.");
};