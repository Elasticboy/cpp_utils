#pragma once

#include "Exception.h"

/*
 * Property Exceptions classes
 */

class load_property_exception : public Exception
{
public:
	load_property_exception(const std::string& source, const std::string& message);// = "Error while loading property.");
};

class save_property_exception : public Exception
{
public:
	save_property_exception(const std::string& source, const std::string& message);// = "Error while saving property.");
};

class read_property_exception : public Exception
{
public:
	read_property_exception(const std::string& source, const std::string& message);// = "Error while reading property.");
};

class write_property_exception : public Exception
{
public:
	write_property_exception(const std::string& source, const std::string& message);// = "Error while writing property.");
};