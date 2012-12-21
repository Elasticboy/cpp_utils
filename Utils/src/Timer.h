#pragma once

#include <string>

class Timer
{
public:
	static std::string getTime(const bool& withSapces);
	static long long counter();
	static long long frequency();
	static double getElapsedTimeMs(long long start, long long finish);
};

