#include "Utils.h"

logger* Utils::logger_ = nullptr;

logger* Utils::get_logger()
{
	if (logger_ == nullptr) {
		logger_ = new logger("default.log");
	}

	return logger_;
}

// TODO: To Implement
//
//#include <memory>
//
//std::shared_ptr<logger> Utils::m_logger = nullptr;
//
//std::shared_ptr<logger> Utils::get_logger()
//{
//	if (m_logger == nullptr) {
//		m_logger = std::make_shared<logger>("default.log");
//	}
//
//	return m_logger;
//}