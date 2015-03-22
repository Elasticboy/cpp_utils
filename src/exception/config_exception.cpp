#include "config_exception.h"

config_exception::config_exception(const std::string& source, const std::string& message) throw()
	: Exception("config_exception", source, message) { }

software_exception::software_exception(const std::string& source, const std::string& message) throw()
	: Exception("software_exception", source, message) { }

platform_exception::platform_exception(const std::string& source) throw()
	: Exception("software_exception", source, "Function not supported on this Operating System") { }
