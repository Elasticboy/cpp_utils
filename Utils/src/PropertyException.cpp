#include "stdafx.h"
#include "PropertyException.h"
#include <iostream>

PropertyException::PropertyException(const std::string& message)
	: m_message(message)
{
	std::cerr << m_message << std::endl;
}

PropertyException::PropertyException(const std::string& message, const std::string& subMessage)
	: m_message(message), m_subMessage(subMessage)
{
	std::cerr << m_message << m_subMessage << std::endl;
}

LoadPropertyException::LoadPropertyException()
	: PropertyException("LoadPropertyException : Error while loading property.")	{ }
LoadPropertyException::LoadPropertyException(const std::string& message)
	: PropertyException("LoadPropertyException : ", message)	{ }

SavePropertyException::SavePropertyException()
	: PropertyException("SavePropertyException : Error while saving property.")		{ }
SavePropertyException::SavePropertyException(const std::string& message)
	: PropertyException("SavePropertyException : ", message)		{ }

ReadPropertyException::ReadPropertyException()
	: PropertyException("ReadPropertyException : Error while reading property.")	{ }
ReadPropertyException::ReadPropertyException(const std::string& message)
	: PropertyException("ReadPropertyException : ", message)	{ }

WritePropertyException::WritePropertyException()
	: PropertyException("ReadPropertyException : Error while writing property.")	{ }
WritePropertyException::WritePropertyException(const std::string& message)
	: PropertyException("ReadPropertyException : ", message)	{ }