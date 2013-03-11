#include "Utils.h"

logger* Utils::m_logger = nullptr;

logger* Utils::getLogger()
{
	if (m_logger == nullptr) {
		m_logger = new logger("default.log");
	}

	return m_logger;
}

// TODO: To Implement
//
//#include <memory>
//
//std::shared_ptr<logger> Utils::m_logger = nullptr;
//
//std::shared_ptr<logger> Utils::getLogger()
//{
//	if (m_logger == nullptr) {
//		m_logger = std::make_shared<logger>("default.log");
//	}
//
//	return m_logger;
//}