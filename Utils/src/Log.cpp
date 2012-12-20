#include "stdafx.h"
#include "Log.h"
#include "FileHandler.h"
#include <sstream>
#include <stdio.h>
// TODO: Clean headers when moving time related functions
#include <ctime>

using namespace std;

Log::Log(const string& filename) : m_LogFile(filename) { }

void Log::info(const std::string& message)
{
	write("INFO  : " + message);
}

void Log::debug(const std::string& message)
{
	write("DEBUG  : " + message);
}

void Log::warning(const std::string& message)
{
	write("WARN  : " + message);
}

void Log::error(const std::string& message)
{
	write("ERROR : " + message);
}

/**
 * Add date and time.
 * Specify the file to write in.
 * Write in the file.
 */
void Log::write(const string& message)
{
	writeInFile(m_LogFile, getTime(true) + " - " + message);
}

void Log::writeInFile(const string& logFilename, const string& message)
{
	FileHandler fwriter(logFilename, FileHandler::OPEN_TYPE_APPEND);
	if (!fwriter.GetFile()) {
		cerr << "Can not open the file '" << message << "' to write !" << endl;
		return;
	}

	fwriter.GetFile() << message << endl;
}

string Log::getTime(const bool& withSapces)
{
	time_t now = time(nullptr);
	tm ltm;
	localtime_s(&ltm, &now);

	// print various components of tm structure.
	const int year	= ltm.tm_year	+ 1900;
	const int month	= ltm.tm_mon	+ 1;
	const int day	= ltm.tm_mday;
	const int hour	= ltm.tm_hour;
	const int min	= ltm.tm_min;
	const int sec	= ltm.tm_sec;
	
	ostringstream oss;
	if (withSapces) {
		oss << year << "-" << month << "-" << day << " " << hour << ":" << min << ":" << sec;
	} else {
		oss << year << "-" << month << "-" << day;
	}
	return oss.str();
}