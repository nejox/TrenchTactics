#include "catch.hpp"
#include "../TrenchTactics/Logger.hpp"
#include<iostream>
#include<fstream>

using namespace std;

inline bool file_exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
inline int getFileSize(std::string filename) // path to file
{
	ifstream in_file(filename, ios::binary);
	in_file.seekg(0, ios::end);
	int file_size = in_file.tellg();
	return file_size;
}
inline string getFileName() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time_t now = time(0);
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d_%m_%Y", timeinfo);
	std::string timestamp(buffer);
	return timestamp;
}


TEST_CASE("Test existence of LogFile") {
	Logger& log = Logger::instance();
	char buff[100];
	snprintf(buff, sizeof(buff), "%s_TrenchTactics.log", getFileName().c_str());
	std::string filename = buff;
	REQUIRE(file_exists(filename));
}

TEST_CASE("Test Additon of Text") {

	Logger::instance();
	int initialSize = getFileSize(getFileName());
	Logger::instance().log(LOGLEVEL::INFO, "UnitTest test log ");
	int sizeAfterLog = getFileSize(getFileName());
	REQUIRE(initialSize <= sizeAfterLog);
}