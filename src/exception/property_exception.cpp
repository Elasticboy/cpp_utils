#include "property_exception.h"

load_property_exception::load_property_exception(const std::string& source, const std::string& message)
	: Exception("load_property_exception", source, message) { }

save_property_exception::save_property_exception(const std::string& source, const std::string& message)
	: Exception("save_property_exception", source, message) { }

read_property_exception::read_property_exception(const std::string& source, const std::string& message)
	: Exception("read_property_exception", source, message) { }

write_property_exception::write_property_exception(const std::string& source, const std::string& message)
	: Exception("read_property_exception", source, message) { }