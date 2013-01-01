#include "stdafx.h"
#include "Lang.h"
#include <regex>

using namespace std;

Lang::Lang(const string& configFile) : Properties(configFile)
{
}

Lang::~Lang(void)
{
}

const string Lang::GetFilename()
{
	return Properties::GetFilePath();
}

const map<string, string> Lang::GetList()
{
	return Properties::GetList();
}

const string Lang::GetText(const string& key)
{
	return  Properties::GetString(key);
}

const string Lang::GetText(const string& key, const string& arg)
{
	const auto& str = Properties::GetString(key);
	const regex regexp("$1");
	return regex_replace(str, regexp, arg);
}