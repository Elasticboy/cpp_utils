#include "stdafx.h"
#include "Logger.h"
#include "FileHandler.h"
#include "Timer.h"
#include <stdio.h>

using namespace std;

const bool QUIET_MODE = false; // If not in QUIET_MODE, write log in console too
const string LOG_DIR = ".\\logs\\";

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
	write(PREFIX_DEBUG + message);
}

void Logger::info(const string& message)
{
	write(PREFIX_INFO + message);
}

void Logger::warning(const string& message)
{
	write(PREFIX_WARNING + message);
}

void Logger::error(const string& message)
{
	write(PREFIX_ERROR + message);
}

/**
 * Add date and time.
 * Specify the file to write in.
 * Write in the file.
 * @param message The message to log.
 */
void Logger::write(const string& message)
{
	try {
		writeInFile(m_logFile, Timer::getTime("%Y-%m-%d %H:%M:%S") + " - " + message);
		if (!QUIET_MODE) {
			cout << message << endl;
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