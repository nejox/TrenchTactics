#include "Logger.h"
#include <fstream>
#include <stdio.h>
#include <ctime> 
#include <experimental/filesystem>


static const char * levelStrings[] = { "Info", "Warning", "Fatal" };

//
Logger::Logger(string className)
{
	this->className = className;
}


//
Logger::~Logger()
{
	this->log(LOGLEVEL::INFO, "Closing Logger Class");
}

void Logger::log(LOGLEVEL level, string message) {
	string msg = getFormatString(level, message);
	this->outputStream.open(this->getLogFileName(), std::ios::app);
	this->outputStream << msg;
	this->outputStream.close();
}

string Logger::getFormatString(LOGLEVEL level, string message)
{
	char buff[200];
	snprintf(buff, sizeof(buff), "%s_%s_%s", getFormattedTimestamp(true), this->className, getTextForEnum(level));
	string formatString = buff;
	return formatString;
}

string Logger::getFormattedTimestamp(boolean datestamp)
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

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

string Logger::getLogFileName()
{
	char buff[100];
	snprintf(buff, sizeof(buff), "%s_trenchTactics.log", getFormattedTimestamp(true));
	string filename = buff;
	return filename;
}

const char * Logger::getTextForEnum(int enumVal)
{
	return levelStrings[enumVal];
}
