#pragma once

#include "Logger.h"

class Utils
{
public:
	static Logger* getLogger();

private:
	static Logger* m_logger;
};

