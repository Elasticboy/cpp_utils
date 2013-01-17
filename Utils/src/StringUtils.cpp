#include "StdAfx.h"
#include "StringUtils.h"
#include <regex>

using namespace std;

bool StringUtils::startsWith(const std::string& str, const std::string& prefix)
{
	if (str.length() < prefix.length()) {
		return false;
	}

	return prefix == str.substr(0, prefix.length());
}

bool StringUtils::endsWith(const std::string& str, const std::string& suffix)
{
	if (str.length() < suffix.length()) {
		return false;
	}

	return suffix == str.substr(str.length() - suffix.length());
}

/**
 * Trim the given string.
 * @param str The string to trim.
 * @return The trimmed string.
 */
const string StringUtils::trim(const string& str)
{
	return lTrim(rTrim(str));
}

/** 
 * Clear a char* buffer.
 * @param _buffer The buffer to clear.
 */
void StringUtils::clearBuffer(char* buffer)
{
	memset(buffer, 0, sizeof(buffer));
	//memset(_buffer, '\0', sizeof(buffer));
}

/**
 * Convert string to bstr_t.
 * @param str The string to convert.
 * @return The converted string.
 */
bstr_t StringUtils::stringToBStr(const string& str)
{
	bstr_t bstr(str.c_str());
	return bstr;
}

const string StringUtils::replaceString(const string& str, const string& pattern, const string& arg)
{
	const regex r(pattern);
	return regex_replace(str, r, arg);
}

const string StringUtils::replaceString(const string& str, const string& pattern, const int& arg)
{
	return replaceStringTemplate(str, pattern, arg);
}

bool StringUtils::isWhitespace(const char& c)
{
	return (c == ' ') || (c == '\t');
}

/**
 * Trim the left part of the given string.
 * @param str The string to trim.
 * @return The left trimmed string.
 */
const string StringUtils::lTrim(const string& str)
{
	string trimmedStr = str;
	while(isWhitespace(trimmedStr.at(0))) {
		trimmedStr = trimmedStr.substr(1);
	}
	return trimmedStr; 
}

/**
 * Trim the right part of the given string.
 * @param str The string to trim.
 * @return The right trimmed string.
 */
const string StringUtils::rTrim(const string& str)
{
	string trimmedStr = str;
	while(isWhitespace(trimmedStr.at(trimmedStr.length() -1))) {
		trimmedStr = trimmedStr.substr(0, trimmedStr.length() -1);
	}
	return trimmedStr; 
}

template<typename T> const string StringUtils::replaceStringTemplate(const string& str, const string& pattern, const T& arg)
{
	return replaceString(str, pattern, to_string(arg));
}