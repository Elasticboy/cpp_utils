#pragma once

#include <iostream>
#include <string>
#include <comdef.h>

class StringUtils
{
public:
	static bool StartWith(const std::string& str, const std::string& startStr);
	static bool EndWith(const std::string& str, const std::string& endStr);
	static const std::string Trim(const std::string& str);
	static void ClearBuffer(char* buffer);
	static bstr_t StringToBStr(const std::string& str);

private:
	static bool IsWhitespace(const char& c);
	static const std::string LTrim(const std::string& str);
	static const std::string RTrim(const std::string& str);
};