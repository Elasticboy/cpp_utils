#pragma once

#include "logger.h"

class Utils
{
public:
	static logger* get_logger();
	//static std::shared_ptr<logger> get_logger();

private:
	static logger* logger_;
	//static std::shared_ptr<logger> m_logger;
};

