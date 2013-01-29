#pragma once

#include <string>

class Timer
{
public:
	static const std::string getTime(const std::string& format);
	static const long long counter();
	static const long long frequency();
	static const double getElapsedTimeMs(long long start, long long finish);
};

