#pragma once

#include <string>

class timer
{
public:
	const std::string current_time(const std::string& format);
	const long long counter();
	const long long frequency();
	const double elapsed_time_ms(long long start, long long finish);

};
