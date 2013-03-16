#include "Exception.h"

#include <iostream>

Exception::Exception(const std::string& type, const std::string& source, const std::string& message) throw()
	: m_type(type), m_source(source), m_message(message) { }

Exception::~Exception() throw() { }

const char* Exception::what() const throw()
{
	return whatAsString().c_str();
}

const std::string Exception::whatAsString() const throw()
{
	return m_type + " : " + m_source + ", " + m_message;
}

const std::string Exception::simpleMessage() const throw()
{
	return m_message;
}
