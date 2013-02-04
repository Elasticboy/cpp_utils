#pragma once

#include <string>
#include <type_traits>
#include <map>
#include "Lang.h"

class Translator
{
public:
	static const std::string LANG_EN;
	static const std::string LANG_FR;
	static Translator* getInstance();
	static void freeInstance();

	//TODO: clean
	/**/
	static std::string getString(const std::string& key, const std::string& arg = "");
	static std::string getString(const std::string& key, const int& arg);
	/**/
	/*/
	template<typename T>
	static std::string getString(const std::string& key, const T& arg = "")
	{
		if (std::is_arithmetic<T>::type() || is_literal_type<T>::type()) {
			return getInstance()->getStringWithArg(key, std::to_string(arg));

		} else if (std::is_same<T, std::string>::type()) {
			return getInstance()->getStringWithArg(key, arg);
		}

		// TODO: Throw (bad argument) an error here !
		//Utils::getLogger()->error("Template getString(), bad argument.");
		throw invalid_argument("Translator::getString() does not accept argument type \"" + typeid(T).name() + "\".");
	}
	/**/
	/*/
	template<typename T>
	static std::string getString(const std::string& key, const T& arg = "")
	{
		getStringHelper(key, arg, std::is_arithmetic<T>::type() || is_literal_type<T>::type());
	}

	template<typename T>
	static std::string getStringHelper(const std::string& key, const T& arg, std::true_type)
	{
		return getInstance()->getStringWithArg(key, std::to_string(arg));
	}

	template<typename T>
	static std::string getStringHelper(const std::string& key, const T& arg, std::false_type)
	{
		return getInstance()->getStringWithArg(key, arg);
	}

	static std::string getString(const std::string& key);
	/**/
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
