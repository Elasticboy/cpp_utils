#include "Translator.h"

#include <type_traits>

#include "exception\ConfigException.h"
#include "Utils.h"

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
		Utils::getLogger()->debug("Translator::setLanguage(), new language \"" + languageKey + "\".");
		return;
	}

	Utils::getLogger()->debug("Translator::setLanguage(" + languageKey + ")");
	throw ConfigurationException("Translator::setLanguage()", "Language \"" + languageKey + "\" is not part of the list. Translator has perhaps not been properly initialized.");
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
		Utils::getLogger()->debug("Translator::addLanguage(), Language \"" + languageKey + "\" already added.");
		return;
	}

	// Key does not exist. Add the file
	m_langFiles.insert(make_pair(languageKey, Lang(dataFile)));
	Utils::getLogger()->debug("Translator::addLanguage(), Language \"" + languageKey + "\" added to the translator.");
}

//TODO: use templates for arg != string (ex : int, double, ...) => type_traits
/*/
template<typename T>
string Translator::getString(const string& key, const T& arg)
{
	if (typename is_arithmetic<T>::type() == true_type) {
		return getInstance()->getStringWithArg(key, to_string(arg));

	} else if (typename is_same<T, string>::type() == true_type) {
		return getInstance()->getStringWithArg(key, arg);
	}

	// TODO: Throw (bad argument) an error here !
	Utils::getLogger()->error("Template getString(), bad argument.");
	throw invalid_argument;
}/**/

/**/
string Translator::getString(const string& key, const string& arg)
{
	return getInstance()->getStringWithArg(key, arg);
}

string Translator::getString(const string& key, const int& arg)
{
	return getInstance()->getStringWithArg(key, to_string(arg));
}
/**/

// TODO: to fix !
/*/
string Translator::getString(const string& key)
{
	return getInstance()->getStringWithArg(key, "");
}
/**/

string Translator::getStringWithArg(const string& key, const string& arg)
{
	for (auto langFile : m_langFiles) {
		if (langFile.first == m_languageKey) {
			return langFile.second.getText(key, arg);
		}
	}
	return ""; // TODO: Throw exception here StringNotFound
}

// TODO: clean
/*
string Translator::getStringArgInt(const std::string& key, const int& arg)
{
	return getStringArgStr(key, to_string(arg));
}
*/

/**
 * The translator is concidered initialized if at least on language is set.
 * @return True if the number of registered languages is superior to zero.
 */
bool Translator::isInitialized()
{
	return m_langFiles.size() > 0;
}