#include "string_utils.h"

#include <regex>

using namespace std;

/**
* Test if a string begins by a given substring.
* @param str The string to test.
* @param prefix The string to be expected at the begining of the tested string.
* @return True if the string starts with the given prefix. False otherwise.
*/
bool string_utils::starts_with(const std::string& str, const std::string& prefix)
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
* @return True if the string ends with the given suffix. Flase otherwise.
*/
bool string_utils::ends_with(const std::string& str, const std::string& suffix)
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
void string_utils::clear_buffer(char* buffer)
{
	memset(buffer, 0, sizeof(buffer));
	//memset(_buffer, '\0', sizeof(buffer));
}

/**
* Convert string to bstr_t.
* @param str The string to convert.
* @return The converted string.
*/
bstr_t string_utils::string_to_bstr(const string& str)
{
	bstr_t bstr(str.c_str());
	return bstr;
}

/**
* Convert a std::string into a std::wstring
*/
wstring string_utils::string_to_wstring(const string& str)
{
	// TODO: write Unit Test
	// TODO: Modif for non ASCII characters
	return wstring(str.begin(), str.end());
}

/**
* Convert a std::wstring into a std::string
*/
string string_utils::wstring_to_string(const wstring& wstr)
{
	// TODO: write Unit Test
	// TODO: Modif for non ASCII characters
	return string(wstr.begin(), wstr.end());
}

bool string_utils::is_whitespace(const char& c)
{
	return (c == ' ') || (c == '\t');
}

/**
* Remove the caracters to the left of a string if they are filtered by the given function.
* @param str The string to clear.
* @param filter The filter function.
* @return The left cleared string.
*/
const string string_utils::clear_left(const string& str, bool (*filter)(const char& c))
{
	string trimmedStr = str;
	while(filter(trimmedStr.at(0))) {
		trimmedStr = trimmedStr.substr(1);
	}
	return trimmedStr; 
}

/**
* Remove the caracters to the right of a string if they are filtered by the given function.
* @param str The string to clear.
* @param filter The filter function.
* @return The right cleared string.
*/
const string string_utils::clear_right(const string& str, bool (*filter)(const char& c))
{
	string trimmedStr = str;
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
const string string_utils::trim(const string& str)
{
	return clear_left(clear_right(str, is_whitespace), is_whitespace);
}

const string string_utils::replace_string(const string& str, const string& pattern, const string& arg)
{
	const regex r(pattern);
	return regex_replace(str, r, arg);
}

const string string_utils::replace_string(const string& str, const string& pattern, const int& arg)
{
	return replace_string_template(str, pattern, arg);
}

template<typename T> const string string_utils::replace_string_template(const string& str, const string& pattern, const T& arg)
{
	return replace_string(str, pattern, to_string(arg));
}