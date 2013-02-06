#include "Exception.h"

#include <iostream>

Exception::Exception(std::string message)
	: m_message(message)
{
	std::cerr << m_message << std::endl;
}

const char* Exception::what() const throw()
{
	return m_message.c_str();
}

std::string Exception::nestedMessage() const throw()
{
	return m_nestedMessage;
}