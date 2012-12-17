#include "StdAfx.h"
#include "StringUtils.h"

using namespace std;

bool StringUtils::StartWith(const std::string& str, const std::string& startStr)
{
	return startStr == str.substr(0, startStr.length());
}

bool StringUtils::EndWith(const std::string& str, const std::string& endStr)
{
	return endStr == str.substr(str.length() - endStr.length());
}


/**
 * Trim the left part of the given string.
 * @param str The string to trim.
 * @return The left trimmed string.
 */
const string StringUtils::LTrim(const string& str)
{
	string trimmedStr = str;
	while(IsWhitespace(trimmedStr.at(0))) {
		trimmedStr = trimmedStr.substr(1);
	}
	return trimmedStr; 
}

/**
 * Trim the right part of the given string.
 * @param str The string to trim.
 * @return The right trimmed string.
 */
const string StringUtils::RTrim(const string& str)
{
	string trimmedStr = str;
	while(IsWhitespace(trimmedStr.at(trimmedStr.length() -1))) {
		trimmedStr = trimmedStr.substr(0, trimmedStr.length() -1);
	}
	return trimmedStr; 
}

/**
 * Trim the given string.
 * @param str The string to trim.
 * @return The trimmed string.
 */
const string StringUtils::Trim(const string& str)
{
	return LTrim(RTrim(str));
}

/** 
 * Clear a char* buffer.
 * @param _buffer The buffer to clear.
 */
void StringUtils::ClearBuffer(char* buffer)
{
	memset(buffer, 0, sizeof(buffer));
	//memset(_buffer, '\0', sizeof(buffer));
}

/**
 * Convert string to bstr_t.
 * @param str The string to convert.
 * @return The converted string.
 */
bstr_t StringUtils::StringToBStr(const string& str)
{
	bstr_t bstr(str.c_str());
	return bstr;
}

bool StringUtils::IsWhitespace(const char& c)
{
	return (c == ' ') || (c == '\t');
}