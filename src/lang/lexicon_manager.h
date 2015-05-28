#pragma once

#include <string>
#include <map>
#include "lexicon.h"
#include "../string_utils.h"

class lexicon_manager
{
public:
    static const std::string LANG_EN_UK;
    static const std::string LANG_EN_US;
    static const std::string LANG_FR;

    static lexicon_manager* instance();

    static void free_instance();


    void set_language(const std::string& lang_key);

    void add_language(const std::string& lang_key, const std::string& data_file);

    bool is_initialized();

    static std::string get_string(const std::string& key, const std::string& arg = "");

    template <typename T>
    static std::string get_string(const std::string& key, const T& arg = "")
    {
        auto arg_as_string = string_utils::to_string(arg);
        return get_string(key, arg_as_string);
    }

private:
    static lexicon_manager* instance_;
    std::string language_key_;
    std::map <std::string, lexicon> lexicons_;

    lexicon_manager();
};