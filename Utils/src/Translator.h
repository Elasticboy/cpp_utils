#pragma once

#include <string>
#include <map>
#include "Lang.h"

class Translator
{
public:
	static const std::string LANG_EN;
	static const std::string LANG_FR;
	static Translator* getInstance();
	static void freeInstance();

	template<typename T> static std::string getString(const std::string& key, const T& arg = "");
	static std::string getString(const std::string& key);

	void setLanguage(const std::string& languageKey);
	void addLanguage(const std::string& languageKey, const std::string& dataFile);
	bool isInitialized();

private:
	static Translator* m_instance;
	std::string getStringWithArg(const std::string& key, const std::string& arg = "");
	// TODO: clean header
	//std::string getStringArgInt(const std::string& key, const int& arg);
	
	Translator();
	~Translator();
	std::string m_languageKey;
	std::map<std::string, Lang> m_langFiles;
};
