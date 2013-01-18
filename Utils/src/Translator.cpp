#include "stdafx.h"
#include "Translator.h"
#include "Exception.h"

using namespace std;

const string Translator::LANG_EN = "EN";
const string Translator::LANG_FR = "FR";

Translator* Translator::m_instance = nullptr;

Translator* Translator::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new Translator();
	}
	return move(m_instance);
}

void Translator::freeInstance()
{
	delete(m_instance);
	m_instance = nullptr;
}

Translator::Translator()
{
	m_languageKey = LANG_EN;
}

Translator::~Translator()
{
}

/**
 * Set the language if it is available in m_langFiles.
 */
void Translator::setLanguage(const string& languageKey)
{
	if (m_langFiles.find(languageKey) != m_langFiles.end()) {
		m_languageKey = languageKey;
	}

	throw Exception("Language \"" + languageKey + "\" is not part of the list. Translator has perhaps not been properly initialized.");
}

/**
 * Add a new language to the translator.
 * @param languageKey The key which define the language.
 * @param dataFile The path of the language file.
 */
void Translator::addLanguage(const string& languageKey, const string& dataFile)
{
	// Add only if dosen't exist
	if (m_langFiles.find(languageKey) != m_langFiles.end()) {
		// Key already exists => return.
		return;
	}

	// Key does not exist. Add the file
	m_langFiles.insert(make_pair(languageKey, Lang(dataFile)));
}

string Translator::getString(const string& key)
{
	for (auto langFile : m_langFiles) {
		if (langFile.first == m_languageKey) {
			return langFile.second.getText(key);
		}
	}
	return ""; // TODO: Throw exception here StringNotFound
}

string Translator::getString(const string& key, const string& arg)
{
	for (auto langFile : m_langFiles) {
		if (langFile.first == m_languageKey) {
			return langFile.second.getText(key, arg);
		}
	}
	return ""; // TODO: Throw exception here StringNotFound
}

//TODO: use templates for arg != string (ex : int, double, ...) 
//template<typename T> string Translator::GetString(const string& key, const T& arg)
string Translator::getString(const std::string& key, const int& arg)
{
	return getString(key, to_string(arg));
}

/**
 * The translator is concidered initialized if at least on language is set.
 * @return True if the number of registered languages is superior to zero.
 */
bool Translator::isInitialized()
{
	return m_langFiles.size() > 0;
}