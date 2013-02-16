#include "Exception.h"

#include <iostream>

Exception::Exception(const std::string& type, const std::string& source, const std::string& message) throw()
	: m_source(source), m_message(message) 
{
}

const char* Exception::what() const throw()
{
	std::string message = m_type + " : " + m_source + ", " + m_message;
	return message.c_str();
}

const std::string Exception::simpleMessage() const throw()
{
	return m_message;
}