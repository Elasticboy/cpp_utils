#pragma once

#include <string>

class logger
{
public:
	static const std::string getLogDir();
	logger(const std::string& filename);
	
	void setLogFile(const std::string& filename);
	void setLogSeverity(const int& logSeverity);
	void setLogSeverityConsole(const int& logSeverity);
	void debug(const std::string& message);
	void info(const std::string& message);
	void warning(const std::string& message);
	void error(const std::string& message);

	static const int SEVERITY_LVL_DEBUG;
	static const int SEVERITY_LVL_INFO;
	static const int SEVERITY_LVL_WARNING;
	static const int SEVERITY_LVL_ERROR;
	static const int SEVERITY_LVL_NOLOG;

private:
	static const std::string PREFIX_DEBUG;
	static const std::string PREFIX_INFO;
	static const std::string PREFIX_WARNING;
	static const std::string PREFIX_ERROR;


	std::string m_logFile;
	int m_logSeverity;
	int m_logSeverityConsole;

	void write(const int& severity, const std::string& message);
};

void appendInFile(const std::string& filename, const std::string& message);