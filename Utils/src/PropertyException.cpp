#include "stdafx.h"
#include "PropertyException.h"
#include <iostream>

PropertyException::PropertyException(const std::string& message)
	: m_message(message)
{
	std::cerr << m_message << std::endl;
}

const char* PropertyException::what() const throw()
{
	return m_message.c_str();
}

LoadPropertyException::LoadPropertyException(const std::string& message)
	: PropertyException("LoadPropertyException : "	+ message) { }

SavePropertyException::SavePropertyException(const std::string& message)
	: PropertyException("SavePropertyException : "	+ message) { }

ReadPropertyException::ReadPropertyException(const std::string& message)
	: PropertyException("ReadPropertyException : "	+ message) { }

WritePropertyException::WritePropertyException(const std::string& message)
	: PropertyException("ReadPropertyException : "	+ message) { }