#include "stdafx.h"
#include "Translator.h"

using namespace std;

const string Translator::LANG_EN = "EN";
const string Translator::LANG_FR = "FR";

unique_ptr<Translator> Translator::m_instance = nullptr;

unique_ptr<Translator> Translator::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = unique_ptr<Translator>(new Translator());
	}
	return move(m_instance);
}

Translator::Translator()
{
}

Translator::~Translator()
{
}

/**
 * Add a new language to the translator.
 * languageKey The key which define the language.
 * dataFile The path of the language file.
 */
void Translator::AddLanguage(string languageKey, string dataFile)
{
	// Add only if dosen't exist
	if (m_langFiles.find(languageKey) != m_langFiles.end()) {
		return;
	}

	m_langFiles.insert(make_pair(languageKey, Lang(dataFile)));
}

string Translator::GetString(const string& key, const string& languageKey)
{
	for (auto langFile : m_langFiles) {
		if (langFile.first == languageKey) {
			return langFile.second.GetText(key);
		}
	}
	
	return ""; // TODO: Throw exception here
}