#include "Logger.hpp"
#include <fstream>
#include <stdio.h>
#include <ctime> 
const char* levelStrings[] = { "Info", "Warning", "Fatal" };

Logger::Logger() {
	this->className = "Test";
	
}

/*
/// <summary>
///
/// </summary>
/// <param name="className"></param>
Logger::Logger(string className)
{
	this->outputStream = std::ofstream();
	this->className = className;
	const char* levelStrings[] = { "Info", "Warning", "Fatal" };
}*/


/// <summary>
/// 
/// </summary>
Logger::~Logger()
{
	this->log(LOGLEVEL::INFO, "Closing Logger Class");
}

/// <summary>
/// 
/// </summary>
/// <param name="level"></param>
/// <param name="message"></param>
void Logger::log(LOGLEVEL level, string message) {
	string msg = getFormatString(level, message);
	this->outputStream.open(this->getLogFileName(), std::ios::app);
	this->outputStream << msg;
	this->outputStream.close();
}

/// <summary>
/// 
/// </summary>
/// <param name="level"></param>
/// <param name="message"></param>
/// <returns></returns>
string Logger::getFormatString(LOGLEVEL level, string message)
{
	char buff[200];
	snprintf(buff, sizeof(buff), "%s_%s_%s", getFormattedTimestamp(true).c_str(), this->className.c_str(), getTextForEnum(level));
	string formatString = buff;
	return formatString;
}

/// <summary>
/// 
/// </summary>
/// <param name="datestamp"></param>
/// <returns></returns>
string Logger::getFormattedTimestamp(boolean datestamp)
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
	string timestamp(buffer);
	return timestamp;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
string Logger::getLogFileName()
{
	char buff[100];
	snprintf(buff, sizeof(buff), "%s_TrenchTactics.log", getFormattedTimestamp(true).c_str());
	string filename = buff;
	return filename;
}

/// <summary>
/// 
/// </summary>
/// <param name="enumVal"></param>
/// <returns></returns>
const char* Logger::getTextForEnum(int enumVal)
{
	return levelStrings[enumVal];
}
