#pragma once

#include <string>

class Logger
{
public:
	Logger(const std::string& filename);
	
	void setLogFile(const std::string& filename);
	void debug(const std::string& message);
	void info(const std::string& message);
	void warning(const std::string& message);
	void error(const std::string& message);

	static const int SEVERITY_DEBUG;
	static const int SEVERITY_INFO;
	static const int SEVERITY_WARNING;
	static const int SEVERITY_ERROR;

private:
	std::string m_logFile;

	void write(const int& severity, const std::string& message);
	void writeInFile(const std::string& filename, const std::string& message);
	
	static const int LOG_SEVERITY;
	static const int LOG_SEVERITY_CONSOLE;
	static const std::string LOG_DIR;

	static const std::string PREFIX_DEBUG;
	static const std::string PREFIX_INFO;
	static const std::string PREFIX_WARNING;
	static const std::string PREFIX_ERROR;
};