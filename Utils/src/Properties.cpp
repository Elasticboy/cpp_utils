#include "Properties.h"

#include <sstream>

#include "string_utils.h"
#include "Utils.h"
#include "exception/property_exception.h"

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
 * @throw read_property_exception if the key is not found.
 */
const string Properties::getString(const string& key)
{
	for (const auto& prop : m_properties) {
		if (prop.first == key) {
			return prop.second;
		}
	}

	Utils::getLogger()->warning("Properties::getString(" + key + ") : Key \"" + key + "\" not found in file \"" + m_filePath + "\".");
	throw read_property_exception("Properties::getString()", "Key \"" + key + "\" not found in file \"" + m_filePath + "\".");
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if read_property_exception is raised.
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
 * @throw read_property_exception if the key is not found.
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
 * @throw read_property_exception cast from string to int fails.
 */
const int Properties::getInt(const string& key)
{
	auto propertyAsString = getString(key);
	return stoi(propertyAsString);
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if read_property_exception is raised.
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
 * @throw read_property_exception if the key is not found.
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

	throw read_property_exception("Properties::getBool()", "Can not convert \"" + stringProperty + "\" to a boolean in file \"" + m_filePath + "\".");
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if read_property_exception is raised.
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
 * @throw read_property_exception if the key is not found.
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
	file_handler fh(path, fh_open_mode::open_mode::read);
	if (!fh.getFile()) {
		throw load_property_exception("Properties::loadProperties()", "Can not open the file \"" + path + "\" to read !");
	}

	try {
		string line;
		while(getline(fh.getFile(), line)) {

			// Ingnore empty lines and lines that begin with "#" (considered as comments)
			if (line.empty() || string_utils::starts_with(string_utils::trim(line), "#")) {
				continue;
			}

			const int equalPos	= line.find('=');
			if (equalPos != string::npos) {
				const string key	= string_utils::trim(line.substr(0, equalPos));
				const string value	= string_utils::trim(line.substr(equalPos + 1));
				m_properties[key] = value;
			}
		}
	} catch (const exception& e) {
		throw load_property_exception("Properties::loadProperties()", "An error occured while parsing the property file \"" + path + "\" : " + e.what());
	}
}

void Properties::saveProperties(const string& path)
{
	file_handler fh(path, fh_open_mode::open_mode::write);
	if (!fh.getFile()) {
		throw save_property_exception("Properties::saveProperties()", "Can not open the file \"" + path + "\" to write !");
	}

	try {
		for (const auto& prop : m_properties) {
			fh.getFile() << prop.first << "=" << prop.second << endl;
		}
	} catch(const exception&) {
		throw save_property_exception("Properties::saveProperties()", "Error while saving the properties in the file \"" + path + "\".");
	}
}

void Properties::saveProperties()
{
	saveProperties(m_filePath);
}
