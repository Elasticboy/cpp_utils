#include "stdafx.h"
#include "Logger.h"
#include "FileHandler.h"
#include "Timer.h"
#include <stdio.h>

using namespace std;

const int LOG_SEVERITY = 4;
const int LOG_SEVERITY_CONSOLE = 4;

const string LOG_DIR = ".\\logs\\";

const int SEVERITY_DEBUG	= 4;
const int SEVERITY_INFO		= 3;
const int SEVERITY_WARNING	= 2;
const int SEVERITY_ERROR	= 1;

const string PREFIX_DEBUG	= "DEBUG : ";
const string PREFIX_INFO	= "INFO  : ";
const string PREFIX_WARNING	= "WARN  : ";
const string PREFIX_ERROR	= "ERROR : ";

Logger::Logger(const string& filename) : m_logFile(LOG_DIR + filename) { }

void Logger::setLogFile(const string& filename)
{
	m_logFile = LOG_DIR + filename;
}

void Logger::debug(const string& message)
{
	write(SEVERITY_DEBUG, message);
}

void Logger::info(const string& message)
{
	write(SEVERITY_INFO, message);
}

void Logger::warning(const string& message)
{
	write(SEVERITY_WARNING, message);
}

void Logger::error(const string& message)
{
	write(SEVERITY_ERROR, message);
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
	if (severity == SEVERITY_DEBUG) {
		prefix = PREFIX_DEBUG;

	} else if (severity == SEVERITY_INFO) {
		prefix = PREFIX_INFO;

	} else if (severity == SEVERITY_WARNING) {
		prefix = PREFIX_WARNING;

	} else if (severity == SEVERITY_ERROR) {
		prefix = PREFIX_ERROR;
	}

	try {
		if (severity <= LOG_SEVERITY) {
			writeInFile(m_logFile, Timer::getTime("%Y-%m-%d %H:%M:%S") + " - " + prefix + message);
		}
		if (severity <= LOG_SEVERITY_CONSOLE) {
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