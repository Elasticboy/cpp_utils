#include "StdAfx.h"
#include "Properties.h"
#include "StringUtils.h"
#include "Utils.h"
#include <sstream>

using namespace std;

Properties::Properties(const string& path) : m_filePath(path)
{
	loadProperties(m_filePath);
}

Properties::~Properties() {}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as a string.
 * @throw ReadPropertyException if the key is not found.
 */
const string Properties::getString(const string& key)
{
	for (const auto& prop : m_properties) {
		if (prop.first == key) {
			return prop.second;
		}
	}

	Utils::getLogger()->warning("Properties::getString(" + key + ") : Key \"" + key + "\" not found in file \"" + m_filePath + "\".");
	throw ReadPropertyException("Key \"" + key + "\" not found in file \"" + m_filePath + "\".");
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if ReadPropertyException is raised.
 * @return The value of the property as a string.
 */
const string Properties::getString(const string& key, const string& defaultValue)
{
	try {
		return getString(key);
	} catch (const exception&) {
		Utils::getLogger()->warning("Properties::getString() : Using default value \"" + defaultValue + "\" for key \"" + key + "\".");
		return defaultValue;
	}
}

/**
 * Set the property value that matches the key.
 * @param key The key of the property.
 * @param value The value to set.
 * @throw ReadPropertyException if the key is not found.
 */
void Properties::setString(const string& key, const string& value)
{
	for (auto& prop : m_properties) {
		if (prop.first == key) {
			prop.second = value;
			return;
		}
	}
	
	Utils::getLogger()->warning("Properties::setString(), The key \"" + key + "\" does not exist in file \"" + m_filePath + "\".");
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as an integer.
 * @throw ReadPropertyException cast from string to int fails.
 */
const int Properties::getInt(const string& key)
{
	auto propertyAsString = getString(key);
	return stoi(propertyAsString);
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if ReadPropertyException is raised.
 * @return The value of the property as an integer.
 */
const int Properties::getInt(const string& key, const int& defaultValue)
{
	try {
		return getInt(key);
	} catch (const exception&) {
		return defaultValue;
	}
}

/**
 * Set the property value that matches the key.
 * @param key The key of the property.
 * @param value The value to set.
 * @throw ReadPropertyException if the key is not found.
 */
void Properties::setInt(const string& key, const int& value)
{
	setString(key, to_string(value));
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as a boolean.
 */
const bool Properties::getBool(const string& key)
{
	auto stringProperty = getString(key);
	if (stringProperty == "true") {
		return true;
	} else if (stringProperty == "false") {
		return false;
	}

	throw ReadPropertyException("Can not convert \"" + stringProperty + "\" to a boolean in file \"" + m_filePath + "\".");
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if ReadPropertyException is raised.
 * @return The value of the property as a boolean.
 */
const bool Properties::getBool(const string& key, const bool& defaultValue)
{
	try {
		return getBool(key);
	} catch (const exception&) {
		return defaultValue;
	}
}

/**
 * Set the property value that matches the key.
 * @param key The key of the property.
 * @param value The value to set.
 * @throw ReadPropertyException if the key is not found.
 */
void Properties::setBool(const string& key, const bool& value)
{
	const string valueAsString = (value) ? "true" : "false";
	setString(key, valueAsString);
}

/**
 * Load the properties from a file.
 * @param path : The property file to read.
 */
void Properties::loadProperties(const string& path)
{
	FileHandler fh(path, FileHandler::OPEN_MODE_READ);
	if (!fh.getFile()) {
		throw LoadPropertyException("Can not open the file \"" + path + "\" to read !");
	}

	try {
		string line;
		while(getline(fh.getFile(), line)) {

			// Ingnore empty lines and lines that begin with "#" (considered as comments)
			if (line.empty() || StringUtils::startsWith(StringUtils::trim(line), "#")) {
				continue;
			}

			const int equalPos	= line.find('=');
			if (equalPos != string::npos) {
				const string key	= StringUtils::trim(line.substr(0, equalPos));
				const string value	= StringUtils::trim(line.substr(equalPos + 1));
				m_properties[key] = value;
			}
		}
	} catch (const exception& e) {
		throw LoadPropertyException("An error occured while parsing the property file \"" + path + "\" : " + e.what());
	}
}

void Properties::saveProperties(const string& path)
{
	FileHandler fh(path, FileHandler::OPEN_MODE_WRITE);
	if (!fh.getFile()) {
		throw SavePropertyException("Can not open the file \"" + path + "\" to write !");
	}

	try {
		for (const auto& prop : m_properties) {
			fh.getFile() << prop.first << "=" << prop.second << endl;
		}
	} catch(const exception&) {
		throw SavePropertyException("Error while saving the properties in the file \"" + path + "\".");
	}
}

void Properties::saveProperties()
{
	saveProperties(m_filePath);
}