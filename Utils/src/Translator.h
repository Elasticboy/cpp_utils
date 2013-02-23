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

	static std::string getString(const std::string& key, const std::string& arg = "");

	void setLanguage(const std::string& languageKey);
	void addLanguage(const std::string& languageKey, const std::string& dataFile);
	bool isInitialized();

private:
	static Translator* m_instance;

	Translator();
	~Translator();
	std::string m_languageKey;
	std::map<std::string, Lang> m_langFiles;


};

namespace trad {
	/** string */
	template<typename T> std::string helperString(const std::string& key, const T& arg, std::true_type)
	{
		return Translator::getString(key, arg);
	}

	/** NOT string => fail */
	template<typename T> std::string helperString(const std::string& key, const T& arg, std::false_type)
	{
		throw invalid_argument("Translator::getString() does not accept argument type \"" + typeid(T).name() + "\".");
	}

	/** literal */
	template<typename T> std::string helperLiteral(const std::string& key, const T& arg, std::true_type)
	{
		return Translator::getString(key, std::string(arg));
	}

	/** NOT literal */
	template<typename T> std::string helperLiteral(const std::string& key, const T& arg, std::false_type)
	{
		return helperString(key, arg, std::is_same<T, std::string>::type());;
	}

	/** Arithmetic */
	template<typename T> std::string helperArithmetic(const std::string& key, const T& arg, std::true_type)
	{
		return Translator::getString(key, std::to_string(arg));
	}

	/** NOT Arithmetic => test literal*/
	template<typename T> std::string helperArithmetic(const std::string& key, const T& arg, std::false_type)
	{
		return helperLiteral(key, arg, std::is_literal_type<T>::type());
	}

	template<typename T> std::string get_string(const std::string& key, const T& arg = "")
	{
		return helperArithmetic(key, arg, std::is_arithmetic<T>::type());
	}

}