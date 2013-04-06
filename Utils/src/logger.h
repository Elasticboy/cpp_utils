#pragma once

#include <string>

class logger
{
public:
	static const std::string log_dir();
	logger(const std::string& filename);
	
	void set_log_file(const std::string& filename);
	void set_log_severity(const int& log_severity);
	void set_log_severity_console(const int& log_severity);
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

	std::string log_file_;
	int log_severity_;
	int log_severity_console_;

	void write(const int& severity, const std::string& message);
};

void append_in_file(const std::string& filename, const std::string& message);