#include "lexicon.h"

#include <regex>
#include "logger/console_logger.h"

lexicon::lexicon(const std::string& configFile)
	: properties(configFile) { }

lexicon::~lexicon(void) { }

const std::string lexicon::filename() const
{
	return properties::get_file_path();
}

const std::map<std::string, std::string> lexicon::list() const
{
	return properties::get_list();
}

const std::string lexicon::item(const std::string& key, const std::string& arg)
{
	const auto str = properties::get_string(key);
	if (arg == "") {
		return str;
	}

	std::smatch match;
	const std::regex r("\\$1");

	if (!std::regex_search(str, match, r)) {

		auto logger = ConsoleLogger(DEBUG);
		logger.Warning("Lang::getText(), No $1 found for the key : \"" + key + "\". Argument \"" + arg + "\" is useless !");
		logger.Warning("Lang::getText(), Consider using Lang::GetText(key) instead of Lang::GetText(key, arg)");
	}
	
	return regex_replace(str, r, arg);
}