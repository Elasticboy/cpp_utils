#pragma once

#include "Exception.h"

/*
 * Property Exceptions classes
 */

class load_property_exception : public Exception
{
public:
    // = "Error while loading property.");
    load_property_exception(const std::string& source, const std::string& message);
};

class save_property_exception : public Exception
{
public:
    // = "Error while saving property.");
    save_property_exception(const std::string& source, const std::string& message);
};

class read_property_exception : public Exception
{
public:
    // = "Error while reading property.");
    read_property_exception(const std::string& source, const std::string& message);
};

class write_property_exception : public Exception
{
public:
    // = "Error while writing property.");
    write_property_exception(const std::string& source, const std::string& message);
};