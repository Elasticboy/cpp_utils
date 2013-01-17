#pragma once

#include <string>
#include <exception>

/**
 * Mother class for exceptions.
 */
class Exception : public std::exception
{
public:
	Exception(std::string message) throw();
	virtual const char* what() const throw();
	virtual std::string nestedMessage() const throw();

protected:
	std::string m_message;
	std::string m_nestedMessage;
};

