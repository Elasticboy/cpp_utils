#pragma once

#include "Exception.h"

/**
 * Configuration Exception : occure when the programme is not properly initialized.
 */
class config_exception : public Exception
{
public:
	config_exception(const std::string& source, const std::string& message);
};