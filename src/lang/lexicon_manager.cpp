#include "lexicon_manager.h"

#include "logger/console_logger.h"
#include "../exception/config_exception.h"

using namespace std;

const string lexicon_manager::LANG_EN_UK = "UK";
const string lexicon_manager::LANG_EN_US = "US";
const string lexicon_manager::LANG_FR = "FR";
lexicon_manager *lexicon_manager::instance_ = nullptr;

lexicon_manager *lexicon_manager::instance()
{
    if (instance_ == nullptr) {
        instance_ = new lexicon_manager();
    }
    return move(instance_);
}

void lexicon_manager::free_instance()
{
    delete(instance_);
    instance_ = nullptr;
}

lexicon_manager::lexicon_manager()
        : language_key_(LANG_EN_US), log_(ConsoleLogger(DEBUG)) { }

/**
 * Set the language if it is available in lexicon_map_.
 */
void lexicon_manager::set_language(const string& language_key)
{
    if (lexicons_.find(language_key) != lexicons_.end()) {
        language_key_ = language_key;
        log_.Debug("lexicon_manager::setLanguage(), new language \"" + language_key + "\".");
        return;
    }

    throw config_exception("lexicon_manager::setLanguage()",
                           "Language \"" + language_key +
                           "\" is not part of the list. lexicon_manager has perhaps not been properly initialized.");
}

/**
 * Add a new language to the lexicon_manager.
 * @param languageKey The key which define the language.
 * @param dataFile The path of the language file.
 */
void lexicon_manager::add_language(const string& language_key, const string& dataFile)
{
    // Add only if doesn't exist
    if (lexicons_.find(language_key) != lexicons_.end()) {
        // Key already exists => return.
        log_.Debug("lexicon_manager::addLanguage(), Language \"" + language_key + "\" already added.");
        return;
    }

    // Key does not exist. Add the file
    lexicons_.insert(make_pair(language_key, lexicon(dataFile)));
    log_.Debug("lexicon_manager::addLanguage(), Language \"" + language_key + "\" added to the lexicon_manager.");
}

/**/
string lexicon_manager::get_string(const string& key, const string& arg)
{
    for (auto langFile : instance_->lexicons_) {
        if (langFile.first == instance_->language_key_) {
            return langFile.second.item(key, arg);
        }
    }

    throw config_exception("lexicon_manager::get_string()", "There is no Key \"" + key + "\" is the file.");
}

/**
 * The lexicon_manager is considered initialized if at least on language is set.
 * @return True if the number of registered languages is superior to zero.
 */
bool lexicon_manager::is_initialized()
{
    return lexicons_.size() > 0;
}
