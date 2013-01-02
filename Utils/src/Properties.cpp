#include "StdAfx.h"
#include "Properties.h"
#include "StringUtils.h"
#include <sstream>

using namespace std;

Properties::Properties(const string& path) : m_FilePath(path)
{
	LoadProperties(m_FilePath);
}

Properties::~Properties() {}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as a string.
 * @throw ReadPropertyException if the key is not found.
 */
const string Properties::GetString(const string& key)
{
	for (const auto& prop : m_Properties) {
		if (prop.first == key) {
			return prop.second;
		}
	}

	throw ReadPropertyException();
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if ReadPropertyException is raised.
 * @return The value of the property as a string.
 */
const string Properties::GetString(const string& key, const string& defaultValue)
{
	try {
		return GetString(key);
	} catch (const ReadPropertyException&) {
		return defaultValue;
	}
}

/**
 * Set the property value that matches the key.
 * @param key The key of the property.
 * @param value The value to set.
 * @throw ReadPropertyException if the key is not found.
 */
void Properties::SetString(const string& key, const string& value)
{
	for (auto& prop : m_Properties) {
		if (prop.first == key) {
			prop.second = value;
			return;
		}
	}

	throw WritePropertyException();
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as an integer.
 * @throw ReadPropertyException cast from string to int fails.
 */
const int Properties::GetInt(const string& key)
{
	auto propertyAsString = GetString(key);
	return stoi(propertyAsString);
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if ReadPropertyException is raised.
 * @return The value of the property as an integer.
 */
const int Properties::GetInt(const string& key, const int& defaultValue)
{
	try {
		return GetInt(key);
	} catch (const ReadPropertyException&) {
		return defaultValue;
	}
}

/**
 * Set the property value that matches the key.
 * @param key The key of the property.
 * @param value The value to set.
 * @throw ReadPropertyException if the key is not found.
 */
void Properties::SetInt(const string& key, const int& value)
{
	SetString(key, to_string(value));
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as a boolean.
 */
const bool Properties::GetBool(const string& key)
{
	auto stringProperty = GetString(key);if (stringProperty == "true") {
		return true;
	} else if (stringProperty == "false") {
		return false;
	}

	throw ReadPropertyException();
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if ReadPropertyException is raised.
 * @return The value of the property as a boolean.
 */
const bool Properties::GetBool(const string& key, const bool& defaultValue)
{
	try {
		return GetBool(key);
	} catch (const ReadPropertyException&) {
		return defaultValue;
	}
}

/**
 * Set the property value that matches the key.
 * @param key The key of the property.
 * @param value The value to set.
 * @throw ReadPropertyException if the key is not found.
 */
void Properties::SetBool(const string& key, const bool& value)
{
	const string valueAsString = (value) ? "true" : "false";
	SetString(key, valueAsString);
}

/**
 * Load the properties from a file.
 * @param path : The property file to read.
 */
void Properties::LoadProperties(const string& path)
{
	FileHandler fh(path, FileHandler::OPEN_TYPE_READ);
	if (!fh.GetFile()) {
		cerr << "Can not open the file to read !" << endl;
		throw LoadPropertyException();
	}

	try {
		string line;
		while(getline(fh.GetFile(), line)) {

			const int equalPos	= line.find('=');

			if (equalPos != -1) {
				const string key	= StringUtils::Trim(line.substr(0, equalPos));
				const string value	= StringUtils::Trim(line.substr(equalPos + 1));
				m_Properties[key] = value;
			}
		}
	} catch (...) {
		throw LoadPropertyException();
	}
}

void Properties::SaveProperties(const string& path)
{
	FileHandler fh(path, FileHandler::OPEN_TYPE_WRITE);
	if (!fh.GetFile()) {
		cerr << "Can not open the file to write !" << endl;
		throw SavePropertyException();
	}

	try {
		for (const auto& prop : m_Properties) {
			fh.GetFile() << prop.first << "=" << prop.second << endl;
		}
	} catch(...) {
		throw SavePropertyException();
	}
}

void Properties::SaveProperties()
{
	SaveProperties(m_FilePath);
}