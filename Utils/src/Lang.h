#pragma once

#include <string>
#include <map>
#include "Properties.h"

class Lang : public Properties
{
public:
	Lang(const std::string& path);
	~Lang(void);
	
	const std::string getFilename();
	const std::map<std::string, std::string> getList();
	const std::string getText(const std::string& key);
	const std::string getText(const std::string& key, const std::string& arg);
};

