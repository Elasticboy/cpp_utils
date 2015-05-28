#pragma once

#include "Exception.h"

/*
 * File Exceptions classes
 */

class file_exception : public Exception
{
public:
    file_exception(const std::string& source, const std::string& message);
};

class open_file_exception : public Exception
{
public:
    open_file_exception(const std::string& source, const std::string& message);
};

class close_file_exception : public Exception
{
public:
    close_file_exception(const std::string& source, const std::string& message);
};

class read_file_exception : public Exception
{
public:
    read_file_exception(const std::string& source, const std::string& message);
};

class write_file_exception : public Exception
{
public:
    write_file_exception(const std::string& source, const std::string& message);
};