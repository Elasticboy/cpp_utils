#pragma once

#include <string>
#include <map>
#include "../properties.h"

class lexicon : public properties
{
public:
    lexicon(const std::string& path);

    ~lexicon(void);

    const std::string filename() const;

    const std::map <std::string, std::string> list() const;

    const std::string item(const std::string& key, const std::string& arg = "");
};

