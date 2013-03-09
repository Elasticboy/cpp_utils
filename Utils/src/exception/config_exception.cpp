#include "config_exception.h"

config_exception::config_exception(const std::string& source, const std::string& message)
	: Exception("config_exception", source, message) { }