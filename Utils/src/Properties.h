#pragma once

#include <string>
#include <map>
#include "FileHandler.h"

class Properties
{
public:
	Properties(const std::string& path);
	~Properties();

protected:
	void loadProperties(const std::string& path);
	void saveProperties(const std::string& path);
	void saveProperties();
	
	const std::string getString(const std::string& key);
	const std::string getString(const std::string& key, const std::string& defaultValue);
	void setString(const std::string& key, const std::string& value);

	const int getInt(const std::string& key);
	const int getInt(const std::string& key, const int& defaultValue);
	void setInt(const std::string& key, const int& value);

	const bool getBool(const std::string& key);
	const bool getBool(const std::string& key, const bool& defaultValue);
	void setBool(const std::string& key, const bool& value);

	const std::map<std::string, std::string> getList() { return m_properties; }
	const std::string getFilePath() { return m_filePath; }

private:
	std::map<std::string, std::string> m_properties;
	std::string m_filePath;
};