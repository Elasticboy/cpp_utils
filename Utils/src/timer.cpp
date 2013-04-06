#include "timer.h"

#include <cstdio>
#include <ctime>
#include <string>
#include "exception/config_exception.h"

#include "platform_config.h"
# if defined(WINDOWS_PLATFORM)
#	include <windows.h>
# endif

namespace timer
{

	/**
	* %a	Abbreviated weekday name		=> Thu
	* %A	Full weekday name				=> Thursday
	* %b	Abbreviated month name			=> Aug
	* %B	Full month name					=> August
	* %c	Date and time representation	=> Thu Aug 23 14:55:02 2001
	* %d	Day of the month (01-31)			=> 23
	* %H	Hour in 24h format (00-23)		=> 14
	* %I	Hour in 12h format (01-12)		=> 02
	* %j	Day of the year (001-366)		=> 235
	* %m	Month as a decimal number (01-12) =>08
	* %M	Minute (00-59)					=> 55
	* %p	AM or PM designation			=> PM
	* %S	Second (00-61)					=> 02
	* %U	Week number with the first Sunday as the first day of week one (00-53) => 33
	* %w	Weekday as a decimal number with Sunday as 0 (0-6) => 4
	* %W	Week number with the first Monday as the first day of week one (00-53) => 34
	* %x	Date representation				=> 08/23/01
	* %X	Time representation				=> 14:55:02
	* %y	Year, last two digits (00-99)	=> 01
	* %Y	Year							=> 2001
	* %Z	Timezone name or abbreviation	=> CDT
	* %%	A % sign						=> %
	*/
	const std::string current_time(const std::string& format)
	{
		const auto buffer_size = 80;
		char buffer[buffer_size];

# if defined(WINDOWS_PLATFORM)
		auto now = time(nullptr);
		tm timeinfo;

		localtime_s(&timeinfo, &now);
		strftime(buffer, buffer_size, format.c_str(), &timeinfo);
# else
		auto now = time(nullptr);
		tm* timeinfo = localtime(&now);
		strftime(buffer, buffer_size, format.c_str(), timeinfo);
# endif

		return std::string(buffer);
	}

	const long long counter()
	{
# if defined(WINDOWS_PLATFORM)
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return li.QuadPart;
#else
		// TODO: Code Linux function for counter()
		//return clock_gettime(CLOCK_REALTIME_HR);
		throw platform_exception("counter()");
# endif
	}

	const long long frequency()
	{
# if defined(WINDOWS_PLATFORM)
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		return li.QuadPart;
#else
		// TODO: Code Linux function for frequency()
		//return clock_gettime(CLOCK_REALTIME_HR);
		throw platform_exception("frequency()");
# endif
	}

	const double elapsed_time_ms(long long start, long long finish)
	{
		return (finish - start) * 1000.0 / frequency();
	}

}
