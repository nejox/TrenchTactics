#ifndef __CLOGFILE
#define __CLOGFILE

// includes
#include <windows.h>
#include <stdio.h>
#include <string>
#include "Singleton.hpp"


// defines
#define string std::string
// enum for loglevels
enum LOGLEVEL
{
	INFO,
	WARNING,
	FATAL //using fatal here because error is already defined
};

// classdeclaration
//
class Logger : public TSingleton<Logger>
{

public:

	Logger(string classname);
	~Logger();
	void log(LOGLEVEL level, string message);


private:
	string className;
	std::ofstream outputStream;
	string getFormatString(LOGLEVEL level, string message);
	string getFormattedTimestamp(boolean datestamp);
	string getLogFileName();
	const char * getTextForEnum(int enumVal);

};
#endif