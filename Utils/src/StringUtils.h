#pragma once

#include <iostream>
#include <string>
#include <comdef.h>

class StringUtils
{
public:
	static bool startWith(const std::string& str, const std::string& startStr);
	static bool endWith(const std::string& str, const std::string& endStr);
	static const std::string trim(const std::string& str);
	static void clearBuffer(char* buffer);
	static bstr_t stringToBStr(const std::string& str);

	static const std::string replaceString(const std::string& str, const std::string& pattern, const std::string& arg);
	static const std::string replaceString(const std::string& str, const std::string& pattern, const int& arg);

private:
	static bool isWhitespace(const char& c);
	static const std::string lTrim(const std::string& str);
	static const std::string rTrim(const std::string& str);
	template<typename T> static const std::string replaceStringTemplate(const std::string& str, const std::string& pattern, const T& arg);
};