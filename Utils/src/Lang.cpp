#include "stdafx.h"

#include "Lang.h"
#include "Utils.h"
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

/**
const string Lang::getText(const string& key)
{
	return Properties::getString(key);
}*/

const string Lang::getText(const string& key, const string& arg)
{
	const auto str = Properties::getString(key);
	if (arg == "") {
		return str;
	}

	smatch match;
	const regex r("\\$1");

	if (!regex_search(str, match, r)) {
		Utils::getLogger()->warning("Lang::getText(), No $1 found for the key : \"" + key + "\". Argument \"" + arg + "\" is useless !");
		Utils::getLogger()->warning("Lang::getText(), Consider using Lang::GetText(key) instead of Lang::GetText(key, arg)");
	}
	
	return regex_replace(str, r, arg);
}