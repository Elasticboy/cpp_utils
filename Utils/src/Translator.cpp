#include "stdafx.h"
#include "Translator.h"
#include <iostream>

using namespace std;

const string Translator::LANG_EN = "EN";
const string Translator::LANG_FR = "FR";

Translator* Translator::m_instance = nullptr;

Translator* Translator::getInstance()
{
	if (m_instance == nullptr) {
		//m_instance = unique_ptr<Translator>(new Translator());
		m_instance = new Translator();
	}
	return move(m_instance);
}

Translator::Translator()
{
	m_languageKey = LANG_EN;
}

Translator::~Translator()
{
}

void Translator::SetLanguage(const string& languageKey){
	m_languageKey = languageKey;
}

/**
 * Add a new language to the translator.
 * languageKey The key which define the language.
 * dataFile The path of the language file.
 */
void Translator::AddLanguage(const string& languageKey, const string& dataFile)
{
	// Add only if dosen't exist
	if (m_langFiles.find(languageKey) != m_langFiles.end()) {
		return;
	}

	m_langFiles.insert(make_pair(languageKey, Lang(dataFile)));
	cout << "AddLanguage langFiles.size() : " << (int) m_langFiles.size() << endl;
}

string Translator::GetString(const string& key)
{
	for (auto langFile : m_langFiles) {
		if (langFile.first == m_languageKey) {
			cout << "GetString(const string& key)" << endl;
			return langFile.second.GetText(key);
		}
	}
	cerr << "langFiles.size() : " << (int) m_langFiles.size() << endl;
	cerr << "m_languageKey : " << m_languageKey << endl;
	return ""; // TODO: Throw exception here StringNotFound
}

string Translator::GetString(const string& key, const string& arg)
{
	for (auto langFile : m_langFiles) {
		if (langFile.first == m_languageKey) {
			cout << "GetString(const string& key, const string& arg)" << endl;
			return langFile.second.GetText(key, arg);
		}
	}
	cerr << "langFiles.size() : " << (int) m_langFiles.size() << endl;
	cerr << "m_languageKey : " << m_languageKey << endl;
	return ""; // TODO: Throw exception here StringNotFound
}