#pragma once

#include <iostream>
#include <string>
#include <comdef.h>

class StringUtils
{
public:
	static bool starts_with(const std::string& str, const std::string& prefix);
	static bool ends_with(const std::string& str, const std::string& suffix);
	static const std::string trim(const std::string& str);
	static const std::string StringUtils::clear_left(const std::string& str, bool (*filter)(const char& c));
	static const std::string StringUtils::clear_right(const std::string& str, bool (*filter)(const char& c));
	static void clear_buffer(char* buffer);
	static bstr_t string_to_bstr(const std::string& str);
	static std::wstring StringUtils::string_to_wstring(const std::string& str);
	static std::string StringUtils::wstring_to_string(const std::wstring& wstr);

	static const std::string replace_string(const std::string& str, const std::string& pattern, const std::string& arg);
	static const std::string replace_string(const std::string& str, const std::string& pattern, const int& arg);

private:
	static bool is_whitespace(const char& c);
	template<typename T> static const std::string replace_string_template(const std::string& str, const std::string& pattern, const T& arg);
};