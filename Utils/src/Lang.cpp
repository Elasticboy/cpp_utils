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

const string Lang::getFilename()
{
	return Properties::getFilePath();
}

const map<string, string> Lang::getList()
{
	return Properties::getList();
}

const string Lang::getText(const string& key)
{
	return Properties::getString(key);
}

const string Lang::getText(const string& key, const string& arg)
{
	const auto str = Properties::getString(key);
	
	// TODO: use regex_find to check useless call to GetText() with arg
	if (str.find("$1") != string::npos) {
		cerr << "No $1 found for the key : \"" << key << "\".";
		cerr << "Consider using Lang::GetText(const string& key) instead of Lang::GetText(const string& key, const string& arg)";
	}
	
	const regex r("\\$1");
	return regex_replace(str, r, arg);
}