#include "Utils.h"

logger* Utils::m_logger = nullptr;

logger* Utils::getLogger()
{
	if (m_logger == nullptr) {
		m_logger = new logger("default.log");
	}

	return m_logger;
}