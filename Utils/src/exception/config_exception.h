#pragma once

#include "Exception.h"

/**
 * Configuration Exception : occure when the programme is not properly initialized.
 */
class config_exception : public Exception
{
public:
	config_exception(const std::string& source, const std::string& message) throw();
};

/**
 * Software exception : occure when the required third party software is not available (e.g. no language installed for TTS or VR).
 */
class software_exception : public Exception
{
public:
	software_exception(const std::string& source, const std::string& message) throw();
};
