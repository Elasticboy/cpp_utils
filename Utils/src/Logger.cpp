#include "stdafx.h"
#include "Logger.h"
#include "FileHandler.h"
#include "Timer.h"
#include <stdio.h>

#define LOG_DIR "logs\\"

using namespace std;

const int DEFAULT_LOG_SEVERITY = 4;
const int DEFAULT_LOG_SEVERITY_CONSOLE = 4;


const string Logger::PREFIX_DEBUG	= "DEBUG : ";
const string Logger::PREFIX_INFO	= "INFO  : ";
const string Logger::PREFIX_WARNING	= "WARN  : ";
const string Logger::PREFIX_ERROR	= "ERROR : ";

const int Logger::SEVERITY_LVL_DEBUG	= 4;
const int Logger::SEVERITY_LVL_INFO		= 3;
const int Logger::SEVERITY_LVL_WARNING	= 2;
const int Logger::SEVERITY_LVL_ERROR	= 1;

Logger::Logger(const string& filename)
{
	setLogFile(filename);
	m_logSeverity			= DEFAULT_LOG_SEVERITY;
	m_logSeverityConsole	= DEFAULT_LOG_SEVERITY_CONSOLE;
}


const string Logger::getLogDir() {
	return LOG_DIR;
}

/**
 * Set the filename for file output.
 * Directory is determine by LOG_DIR.
 */
void Logger::setLogFile(const string& filename)
{
	m_logFile = getLogDir() + filename;
}

/**
 * Set the log severity for file output;
 */
void Logger::setLogSeverity(const int& logSeverity)
{
	m_logSeverity = logSeverity;
}

/**
 * Set the log severity for console output;
 */
void Logger::setLogSeverityConsole(const int& logSeverity)
{
	m_logSeverityConsole = logSeverity;
}

void Logger::debug(const string& message)
{
	write(SEVERITY_LVL_DEBUG, message);
}

void Logger::info(const string& message)
{
	write(SEVERITY_LVL_INFO, message);
}

void Logger::warning(const string& message)
{
	write(SEVERITY_LVL_WARNING, message);
}

void Logger::error(const string& message)
{
	write(SEVERITY_LVL_ERROR, message);
}

/**
 * Add date and time.
 * Specify the file to write in.
 * Write in the file.
 * @param message The message to log.
 */
void Logger::write(const int& severity, const string& message)
{
	string prefix = "";
	if (severity == SEVERITY_LVL_DEBUG) {
		prefix = PREFIX_DEBUG;

	} else if (severity == SEVERITY_LVL_INFO) {
		prefix = PREFIX_INFO;

	} else if (severity == SEVERITY_LVL_WARNING) {
		prefix = PREFIX_WARNING;

	} else if (severity == SEVERITY_LVL_ERROR) {
		prefix = PREFIX_ERROR;
	}

	try {
		if (severity <= m_logSeverity) {
			writeInFile(m_logFile, Timer::getTime("%Y-%m-%d %H:%M:%S") + " - " + prefix + message);
		}
		if (severity <= m_logSeverityConsole) {
			cout << prefix << message << endl;
		}
	} catch (const exception&) {
		cerr << "Can not open the file '" << m_logFile << "' to write !" << endl;
		cout << message << endl;
	}
}

/**
 * Write a maessage in a file.
 * @param logFilename the logfile name.
 * @param message The message to write in the file.
 */
void Logger::writeInFile(const string& logFilename, const string& logMessage)
{	
	FileHandler fwriter(logFilename, FileHandler::OPEN_MODE_APPEND);
	fwriter.getFile() << logMessage << endl;
}