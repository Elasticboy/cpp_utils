#pragma once

#include <string>
#include <map>
#include "Lang.h"
#include "Logger.h"

class Translator
{
public:
	static const std::string LANG_EN;
	static const std::string LANG_FR;
	static Translator* getInstance();
	static void freeInstance();

	void setLanguage(const std::string& languageKey);
	void addLanguage(const std::string& languageKey, const std::string& dataFile);
	std::string getString(const std::string& key);
	std::string getString(const std::string& key, const std::string& arg);
	std::string getString(const std::string& key, const int& arg);
	bool isInitialized();

private:
	static Translator* m_instance;
	static Logger* m_log;
	
	Translator();
	~Translator();
	std::string m_languageKey;
	std::map<std::string, Lang> m_langFiles;
};
