#pragma once

#include <string>
#include <map>
#include "Properties.h"

class Lang : public Properties
{
public:
	Lang(const std::string& path);
	~Lang(void);
	
	const std::string GetFilename();
	const std::map<std::string, std::string> GetList();
	const std::string GetText(const std::string& key);
	const std::string GetText(const std::string& key, const std::string& arg);
};

