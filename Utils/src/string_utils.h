#pragma once

#include <iostream>
#include <string>
#include <type_traits>

#include "platform_config.h"
# if defined(WINDOWS_PLATFORM)
#	include <comdef.h>
# endif

namespace string_utils {

	bool starts_with(const std::string& str, const std::string& prefix);
	bool ends_with(const std::string& str, const std::string& suffix);
	const std::string trim(const std::string& str);
	const std::string clear_left(const std::string& str, bool (*filter)(const char& c));
	const std::string clear_right(const std::string& str, bool (*filter)(const char& c));
	void clear_buffer(char* buffer);

	bool is_whitespace(const char& c);

	/////////////////////////////////////////////////////////////////
	//                      Conversions
	/////////////////////////////////////////////////////////////////

# if defined(WINDOWS_PLATFORM)
	bstr_t string_to_bstr(const std::string& str);
# endif
	std::wstring string_to_wstring(const std::string& str);
	std::string wstring_to_string(const std::wstring& wstr);

	/////////////////////////////////////////////////////////////////
	//                      Templates
	/////////////////////////////////////////////////////////////////

	namespace helper {

		/// Arithmetic
		template<typename T> std::string helper_arithmetic(const T& arg, std::true_type)
		{
			return std::to_string(arg);
		}

		/// NOT Arithmetic
		template<typename T> std::string helper_arithmetic(const T& arg, std::false_type)
		{
			return arg;
		}

		const std::string replace_string(const std::string& str, const std::string& pattern, const std::string& arg);
	}

	template<typename T> std::string to_string(const T& arg)
	{
		return helper::helper_arithmetic(arg, typename std::is_arithmetic<T>::type());
	}

	template<typename T> const std::string replace_string(const std::string& str, const std::string& pattern, const T& arg)
	{
		return helper::replace_string(str, pattern, to_string(arg));
	}

	template<typename T> void securedPrint(char* buffer, const int& length, const char* format, const T& arg) {
# if defined(WINDOWS_PLATFORM)
		sprintf_s(buffer, length, format, arg);
# else
		sprintf(buffer, format, arg);
# endif
	}

}
