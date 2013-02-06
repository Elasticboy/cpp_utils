#include "StdAfx.h"
#include "StringUtils.h"
#include <regex>

using namespace std;

bool StringUtils::starts_with(const std::string& str, const std::string& prefix)
{
	if (str.length() < prefix.length()) {
		return false;
	}

	return prefix == str.substr(0, prefix.length());
}

bool StringUtils::ends_with(const std::string& str, const std::string& suffix)
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
void StringUtils::clear_buffer(char* buffer)
{
	memset(buffer, 0, sizeof(buffer));
	//memset(_buffer, '\0', sizeof(buffer));
}

/**
* Convert string to bstr_t.
* @param str The string to convert.
* @return The converted string.
*/
bstr_t StringUtils::string_to_bstr(const string& str)
{
	bstr_t bstr(str.c_str());
	return bstr;
}

bool StringUtils::is_whitespace(const char& c)
{
	return (c == ' ') || (c == '\t');
}

/**
* Remove the caracters to the left of a string if they are filtered by the given function.
* @param str The string to clear.
* @param filter The filter function.
* @return The left cleared string.
*/
const string StringUtils::clear_left(const string& str, bool (*filter)(const char& c))
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
const string StringUtils::clear_right(const string& str, bool (*filter)(const char& c))
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
const string StringUtils::trim(const string& str)
{
	return clear_left(clear_right(str, is_whitespace), is_whitespace);
}

const string StringUtils::replace_string(const string& str, const string& pattern, const string& arg)
{
	const regex r(pattern);
	return regex_replace(str, r, arg);
}

const string StringUtils::replace_string(const string& str, const string& pattern, const int& arg)
{
	return replace_string_template(str, pattern, arg);
}

template<typename T> const string StringUtils::replace_string_template(const string& str, const string& pattern, const T& arg)
{
	return replace_string(str, pattern, to_string(arg));
}