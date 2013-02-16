#include "ConfigException.h"

ConfigurationException::ConfigurationException(const std::string& source, const std::string& message)
	: Exception("ConfigurationException", source, message) { }