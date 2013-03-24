#include "logger.h"

#include <iostream>

#include "file_handler.h"
#include "timer.h"

#define LOG_DIR "logs/"

using namespace std;

const int DEFAULT_LOG_SEVERITY = 4;
const int DEFAULT_LOG_SEVERITY_CONSOLE = 4;

const int logger::SEVERITY_LVL_DEBUG	= 4;
const int logger::SEVERITY_LVL_INFO		= 3;
const int logger::SEVERITY_LVL_WARNING	= 2;
const int logger::SEVERITY_LVL_ERROR	= 1;
const int logger::SEVERITY_LVL_NOLOG	= 0;

const string logger::PREFIX_DEBUG	= "DEBUG : ";
const string logger::PREFIX_INFO	= "INFO  : ";
const string logger::PREFIX_WARNING	= "WARN  : ";
const string logger::PREFIX_ERROR	= "ERROR : ";

logger::logger(const string& filename) :
	m_logSeverity(DEFAULT_LOG_SEVERITY), m_logSeverityConsole(DEFAULT_LOG_SEVERITY_CONSOLE)
{
	setLogFile(filename);
}


const string logger::getLogDir() {
	return LOG_DIR;
}

/**
 * Set the filename for file output.
 * Directory is determine by LOG_DIR.
 */
void logger::setLogFile(const string& filename)
{
	m_logFile = getLogDir() + filename;
}

/**
 * Set the log severity for file output;
 */
void logger::setLogSeverity(const int& logSeverity)
{
	m_logSeverity = logSeverity;
}

/**
 * Set the log severity for console output;
 */
void logger::setLogSeverityConsole(const int& logSeverity)
{
	m_logSeverityConsole = logSeverity;
}

void logger::debug(const string& message)
{
	write(SEVERITY_LVL_DEBUG, message);
}

void logger::info(const string& message)
{
	write(SEVERITY_LVL_INFO, message);
}

void logger::warning(const string& message)
{
	write(SEVERITY_LVL_WARNING, message);
}

void logger::error(const string& message)
{
	write(SEVERITY_LVL_ERROR, message);
}

/**
 * Add date and time.
 * Specify the file to write in.
 * Write in the file.
 * @param message The message to log.
 */
void logger::write(const int& severity, const string& message)
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
			appendInFile(m_logFile, Timer::getTime("%Y-%m-%d %H:%M:%S") + " - " + prefix + message);
		}
		if (severity <= m_logSeverityConsole) {
			cout << prefix << message << endl;
		}
	} catch (const exception&) {
		cerr << "Can not open the file '" << m_logFile << "' to write !" << endl;
		cout << message << endl;
	}
}

// TODO: Move to file_handler or FileWriter (create the class)
/**
 * Append a message in a file.
 * @param logFilename the logfile to log in.
 * @param message The message to write in the file.
 */
void appendInFile(const string& logFilename, const string& logMessage)
{
	file_handler fwriter(logFilename, fh_open_mode::open_mode::append);
	fwriter.getFile() << logMessage << endl;
}
