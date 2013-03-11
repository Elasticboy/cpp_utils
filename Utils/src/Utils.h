#pragma once

#include "logger.h"

class Utils
{
public:
	static logger* getLogger();
	//static std::shared_ptr<logger> getLogger();

private:
	static logger* m_logger;
	//static std::shared_ptr<logger> m_logger;
};

