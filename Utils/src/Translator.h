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
	static Translator* getInstance();
	//static std::unique_ptr<Translator> getInstance();

	~Translator();
	void SetLanguage(const std::string& languageKey);
	void AddLanguage(const std::string& languageKey, const std::string& dataFile);
	std::string GetString(const std::string& key);
	std::string GetString(const std::string& key, const std::string& arg);

private:
	static Translator* m_instance;
	//static std::unique_ptr<Translator> m_instance;
	
	Translator();
	std::string m_languageKey;
	std::map<std::string, Lang> m_langFiles;
};

