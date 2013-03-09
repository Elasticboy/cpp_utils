#pragma once

#include "logger.h"

class Utils
{
public:
	static logger* getLogger();

private:
	static logger* m_logger;
};

