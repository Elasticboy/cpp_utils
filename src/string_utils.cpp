#include "string_utils.h"

#include <regex>
#include <string.h>

namespace string_utils
{

	/**
	* Test if a string begins by a given substring.
	* @param str The string to test.
	* @param prefix The string to be expected at the beginning of the tested string.
	* @return True if the string starts with the given prefix. False otherwise.
	*/
	bool starts_with(const std::string& str, const std::string& prefix)
	{
		if (str.length() < prefix.length()) {
			return false;
		}

		return prefix == str.substr(0, prefix.length());
	}

	/**
	* Test if a string ends by a given substring.
	* @param str The string to test.
	* @param suffix The string to be expected at the end of the tested string.
	* @return True if the string ends with the given suffix. False otherwise.
	*/
	bool ends_with(const std::string& str, const std::string& suffix)
	{
		if (str.length() < suffix.length()) {
			return false;
		}

		return suffix == str.substr(str.length() - suffix.length());
	}

	/**
	* Clear a char* buffer.
	* @param _buffer The buffer to clear.
	*/
	void clear_buffer(char* buffer)
	{
//		buffer = '\0';
		memset(buffer, 0, sizeof(buffer));
		//memset(_buffer, '\0', sizeof(buffer));
	}

	/**
	* Convert a std::string into a std::wstring
	*/
	std::wstring string_to_wstring(const std::string& str)
	{
		// TODO: write Unit Test
		// TODO: Modify for non ASCII characters
		return std::wstring(str.begin(), str.end());
	}

	/**
	* Convert a std::wstring into a std::string
	*/
	std::string wstring_to_string(const std::wstring& wstr)
	{
		// TODO: write Unit Test
		// TODO: Modify for non ASCII characters
		return std::string(wstr.begin(), wstr.end());
	}

	bool is_whitespace(const char& c)
	{
		return (c == ' ') || (c == '\t');
	}

	/**
	* Remove the characters to the left of a string if they are filtered by the given function.
	* @param str The string to clear.
	* @param filter The filter function.
	* @return The left cleared string.
	*/
	const std::string clear_left(const std::string& str, bool (*filter)(const char& c))
	{
		auto trimmedStr = str;
		while(filter(trimmedStr.at(0))) {
			trimmedStr = trimmedStr.substr(1);
		}
		return trimmedStr;
	}

	/**
	* Remove the characters to the right of a string if they are filtered by the given function.
	* @param str The string to clear.
	* @param filter The filter function.
	* @return The right cleared string.
	*/
	const std::string clear_right(const std::string& str, bool (*filter)(const char& c))
	{
		auto trimmedStr = str;
		while(filter(trimmedStr.at(trimmedStr.length() -1))) {
			trimmedStr = trimmedStr.substr(0, trimmedStr.length() -1);
		}
		return trimmedStr;
	}

	/**
	* Trim the given string.
	* @param str The string to trim.
	* @return The trimmed string.
	*/
	const std::string trim(const std::string& str)
	{
		return clear_left(clear_right(str, is_whitespace), is_whitespace);
	}

	namespace helper {
		const std::string replace_string(const std::string& str, const std::string& pattern, const std::string& arg)
		{
			const std::regex r(pattern);
			return std::regex_replace(str, r, arg);
		}
	}

}