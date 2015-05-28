#pragma once

#include <string>
#include <exception>

/**
 * Mother class for exceptions.
 */
class Exception : public std::exception
{
public:
    Exception(const std::string& type, const std::string& source, const std::string& message) throw();

    ~Exception() throw();

    virtual const char* what() const throw();

    const std::string whatAsString() const throw();

    const std::string simpleMessage() const throw();

private:
    std::string m_type;
    std::string m_source;
    std::string m_message;
};

