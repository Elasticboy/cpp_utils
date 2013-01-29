#pragma once

#include <string>

class Logger
{
public:
	Logger(const std::string& filename);

	void info(const std::string& message);
	void debug(const std::string& message);
	void warning(const std::string& message);
	void error(const std::string& message);

private:
	std::string m_logFile;

	void write(const std::string& message);
	void writeInFile(const std::string& filename, const std::string& message);
};