#include "PropertyException.h"

LoadPropertyException::LoadPropertyException(const std::string& source, const std::string& message)
	: Exception("LoadPropertyException", source, message) { }

SavePropertyException::SavePropertyException(const std::string& source, const std::string& message)
	: Exception("SavePropertyException", source, message) { }

ReadPropertyException::ReadPropertyException(const std::string& source, const std::string& message)
	: Exception("ReadPropertyException", source, message) { }

WritePropertyException::WritePropertyException(const std::string& source, const std::string& message)
	: Exception("ReadPropertyException", source, message) { }