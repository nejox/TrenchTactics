#include "Logger.hpp"
#include <fstream>
#include <stdio.h>
#include <ctime> 
#include "Logger.hpp"

// String array with representations of all loglevels
const char* levelStrings[] = { "Info", "Warning", "Fatal" };



/// <summary>
/// Standard Constructor this is private caused by singelton pattern
/// </summary>
Logger::Logger() {
}

/// <summary>
/// Standard deconstructor also private maybe used from singelton pattern to teardown logger
/// </summary>
Logger::~Logger()
{
}

/// <summary>
/// Main logging method which appends logs to the daily log file
/// Follows the pattern [timestamp] - loglevel - message
/// </summary>
/// <param name="level">Loglevel from enum</param>
/// <param name="message">String representation of the log message</param>
void Logger::log(LOGLEVEL level, std::string message) {
	std::string msg = getFormatString(level, message);
	this->outputStream.open(this->getLogFileName(), std::ios::app);
	this->outputStream << msg;
	this->outputStream.close();
}

/// <summary>
/// Format function for logmessage takes the loglevel and message and produces timestamp
/// Format is open for discussion: [timestamp] - loglevel - message
/// Current class is missing
/// message gets converted to c_string
/// </summary>
/// <param name="level">Loglevel from enum</param>
/// <param name="message">String representation of the log message</param>
/// <returns>the formatted string with timestamp,loglevel and message</returns>
std::string Logger::getFormatString(LOGLEVEL level, std::string message)
{
	char buff[200];
	snprintf(buff, sizeof(buff), "[%s] - %s - %s\n", getFormattedTimestamp(false).c_str(), getTextForEnum(level), message.c_str());
	std::string formatString = buff;
	return formatString;
}

/// <summary>
/// Function that provides timestamp in two different formats
/// either datestamp with format: DD_MM_YY
/// or complete timestamp with format: DD-MM-YY HH:MM:SS
/// </summary>
/// <param name="datestamp">boolean value wether you want a date- or timestamp</param>
/// <returns>the formatted timestamp in string representation</returns>
std::string Logger::getFormattedTimestamp(boolean datestamp)
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time_t now = time(0);
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (datestamp) {
		strftime(buffer, sizeof(buffer), "%d_%m_%Y", timeinfo);
	}
	else {
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	}
	std::string timestamp(buffer);
	return timestamp;
}

/// <summary>
/// Provide logfilename with todays timestamp
/// </summary>
/// <returns>string representation of the log file</returns>
std::string Logger::getLogFileName()
{
	char buff[100];
	snprintf(buff, sizeof(buff), "%s_TrenchTactics.log", getFormattedTimestamp(true).c_str());
	std::string filename = buff;
	return filename;
}

/// <summary>
/// Util function the converts loglevel enum to a string by converting it to an int value and accessing a char* [] with that value
/// </summary>
/// <param name="enumVal">Indirect conversion from enum to int</param>
/// <returns>Loglevel as string</returns>
const char* Logger::getTextForEnum(int enumVal)
{
	return levelStrings[enumVal];
}
