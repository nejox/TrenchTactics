#ifndef __CLOGFILE
#define __CLOGFILE
#define _CRT_SECURE_NO_WARNINGS
// includes
#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>



// enum for loglevels
enum LOGLEVEL
{
	INFO,
	WARNING,
	FATAL //using fatal here because error is already defined
};

/// <summary>
/// Logger class based on singelton pattern
/// </summary>
class Logger
{
public:
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;

	static auto& instance() {
		static Logger logger;
		return logger;
	}
	void log(LOGLEVEL level, std::string message);

private:
	Logger();
	std::ofstream outputStream;
	std::string getFormatString(LOGLEVEL level, std::string message);
	std::string getFormattedTimestamp(boolean datestamp);
	std::string getLogFileName();
	const char* getTextForEnum(int enumVal);

};
#endif