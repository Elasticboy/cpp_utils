#include "stdafx.h"
#include "Utils.h"

Logger* Utils::m_logger = nullptr;

Logger* Utils::getLogger()
{
	if (m_logger == nullptr) {
		m_logger = new Logger("Utils.log");
	}

	return m_logger;
}