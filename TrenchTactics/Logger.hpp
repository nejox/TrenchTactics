#ifndef __CLOGFILE
#define __CLOGFILE
#define _CRT_SECURE_NO_WARNINGS
// includes
#include <windows.h>
#include <stdio.h>
#include <string>
#include "Singleton.hpp"
#include <iostream>
#include <fstream>

// defines
#define string std::string
#define Log Logger::instance()

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
	void log(LOGLEVEL level, string message);
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;

	static auto& instance() {
		static Logger logger;
		return logger;
	}

private:
	Logger();
	std::ofstream outputStream;
	string getFormatString(LOGLEVEL level, string message);
	string getFormattedTimestamp(boolean datestamp);
	string getLogFileName();
	const char* getTextForEnum(int enumVal);

};
#endif