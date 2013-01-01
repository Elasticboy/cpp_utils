#pragma once

#include <string>
#include <map>
#include <memory>
#include "Lang.h"

class Translator
{
public:
	static const std::string LANG_EN;
	static const std::string LANG_FR;
	
	~Translator();
	static std::unique_ptr<Translator> getInstance();
	void AddLanguage(std::string languageKey, std::string dataFile);
	std::string GetString(const std::string& key, const std::string& lang);

private:
	Translator();

	static std::unique_ptr<Translator> m_instance;
	std::map<std::string, Lang> m_langFiles;
};

