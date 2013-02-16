#pragma once

#include "Exception.h"

/**
 * Configuration Exception : occure when the programme is not properly initialized.
 */
class ConfigurationException : public Exception
{
public:
	ConfigurationException(const std::string& source, const std::string& message);// = "Error while loading property.");
};