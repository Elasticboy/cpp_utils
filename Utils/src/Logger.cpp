#include "stdafx.h"
#include "Logger.h"
#include "FileHandler.h"
#include "Timer.h"
#include <stdio.h>

using namespace std;

Logger::Logger(const string& filename) : m_LogFile(filename) { }

void Logger::info(const std::string& message)
{
	write("INFO  : " + message);
}

void Logger::debug(const std::string& message)
{
	write("DEBUG  : " + message);
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
	writeInFile(m_LogFile, Timer::getTime(true) + " - " + message);
}

/**
 * Write a maessage in a file.
 * @param logFilename the logfile name.
 * @param message The message to write in the file.
 */
void Logger::writeInFile(const string& logFilename, const string& message)
{
	FileHandler fwriter(logFilename, FileHandler::OPEN_MODE_APPEND);
	if (!fwriter.getFile()) {
		cerr << "Can not open the file '" << logFilename << "' to write !" << endl;
		cout << message << endl;
		return;
	}

	fwriter.getFile() << message << endl;
}