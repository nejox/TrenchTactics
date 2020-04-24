#include "Logger.hpp"
#include <fstream>
#include <stdio.h>
#include <ctime> 
#include "Logger.hpp"

/**
 * String array with representations of all loglevels.
 */
const char* levelStrings[] = { "Info", "Warning", "Fatal" };

/**
 * Standard Constructor this is private caused by singelton pattern
 * 
 */
Logger::Logger() {
}

/**
 * Standard deconstructor also private maybe used from singelton pattern to teardown logger
 * 
 */
Logger::~Logger()
{
}

/**
 * Main logging method which appends logs to the daily log file
 * Follows the pattern [timestamp] - loglevel - message
 * 
 * \param level Loglevel from enum
 * \param message String representation of the log message
 */
void Logger::log(LOGLEVEL level, std::string message) {
	std::string msg = getFormatString(level, message);
	this->outputStream.open(this->getLogFileName(), std::ios::app);
	this->outputStream << msg;
	this->outputStream.close();
}

/**
 * Format function for logmessage takes the loglevel and message and produces timestamp
 * Format is open for discussion: [timestamp] - loglevel - message
 * Current class is missing
 * message gets converted to c_string
 * 
 * \param level Loglevel from enum
 * \param message String representation of the log message
 * \return the formatted string with timestamp,loglevel and message
 */
std::string Logger::getFormatString(LOGLEVEL level, std::string message)
{
	char buff[200];
	snprintf(buff, sizeof(buff), "[%s] - %s - %s\n", getFormattedTimestamp(false).c_str(), getTextForEnum(level), message.c_str());
	std::string formatString = buff;
	return formatString;
}

/**
 * Function that provides timestamp in two different formats
 * either datestamp with format: DD_MM_YY
 * or complete timestamp with format: DD-MM-YY HH:MM:SS
 * 
 * \param datestamp boolean value wether you want a date- or timestamp
 * \return the formatted timestamp in string representation
 */
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

/**
 * Provide logfilename with todays timestamp
 * 
 * \return string representation of the log file
 */
std::string Logger::getLogFileName()
{
	char buff[100];
	snprintf(buff, sizeof(buff), "%s_TrenchTactics.log", getFormattedTimestamp(true).c_str());
	std::string filename = buff;
	return filename;
}

/**
 * Util function the converts loglevel enum to a string by converting it to an int value and accessing a char* [] with that value
 * 
 * \param enumVal Indirect conversion from enum to int
 * \return Loglevel as string
 */
const char* Logger::getTextForEnum(int enumVal)
{
	return levelStrings[enumVal];
}
