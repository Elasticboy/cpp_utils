#include "stdafx.h"
#include "Timer.h"

#include <windows.h>
#include <sstream>
#include <ctime>
#include <stdio.h>

using namespace std;

// TODO: Fix formatting problem => 2012-12-21 1:7:47
// TODO: change function parameters => format (Y-M-d H:m:s
string Timer::getTime(const bool& withSapces)
{
	time_t now = time(nullptr);
	tm ltm;
	localtime_s(&ltm, &now);

	// print various components of tm structure.
	const int year	= ltm.tm_year	+ 1900;
	const int month	= ltm.tm_mon	+ 1;
	const int day	= ltm.tm_mday;
	const int hour	= ltm.tm_hour;
	const int min	= ltm.tm_min;
	const int sec	= ltm.tm_sec;
	
	ostringstream oss;
	if (withSapces) {
		oss << year << "-" << month << "-" << day << " " << hour << ":" << min << ":" << sec;
	} else {
		oss << year << "-" << month << "-" << day;
	}
	return oss.str();
}

long long Timer::counter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return li.QuadPart;
}

long long Timer::frequency()
{
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	return li.QuadPart;
}

double Timer::getElapsedTimeMs(long long start, long long finish)
{
	return (finish - start) * 1000.0 / frequency();
}