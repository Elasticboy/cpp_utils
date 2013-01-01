#pragma once

#include <string>
#include <map>
#include "FileHandler.h"
#include "PropertyException.h"

class Properties
{
public:
	Properties(const std::string& path);
	~Properties();

protected:
	void LoadProperties(const std::string& path);
	void SaveProperties(const std::string& path);
	void SaveProperties();
	
	const std::string GetString(const std::string& key);
	const std::string GetString(const std::string& key, const std::string& defaultValue);
	void SetString(const std::string& key, const std::string& value);

	const int GetInt(const std::string& key);
	const int GetInt(const std::string& key, const int& defaultValue);
	void SetInt(const std::string& key, const int& value);

	const bool GetBool(const std::string& key);
	const bool GetBool(const std::string& key, const bool& defaultValue);
	void SetBool(const std::string& key, const bool& value);

	const std::map<std::string, std::string> GetList() { return m_Properties; }
	const std::string GetFilePath() { return m_FilePath; }

private:
	std::map<std::string, std::string> m_Properties;
	std::string m_FilePath;
};