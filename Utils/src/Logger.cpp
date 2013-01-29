#include "stdafx.h"
#include "Logger.h"
#include "FileHandler.h"
#include "Timer.h"
#include <stdio.h>

using namespace std;
#define QUIET_MODE true // If not in QUIET_MODE, write log in console too

Logger::Logger(const string& filename) : m_logFile("logs/" + filename) { }

void Logger::info(const std::string& message)
{
	write("INFO  : " + message);
}

void Logger::debug(const std::string& message)
{
	write("DEBUG : " + message);
}

void Logger::warning(const std::string& message)
{
	write("WARN  : " + message);
}

void Logger::error(const std::string& message)
{
	write("ERROR : " + message);
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