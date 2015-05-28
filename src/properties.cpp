#include "properties.h"

#include <sstream>

#include "logger/console_logger.h"
#include "string_utils.h"
#include "exception/property_exception.h"

using namespace std;

auto log = ConsoleLogger(DEBUG);

properties::properties(const string& path) : file_path_(path)
{
    load_properties(file_path_);
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as a string.
 * @throw read_property_exception if the key is not found.
 */
const string properties::get_string(const string& key)
{
    for (const auto& prop : properties_) {
        if (prop.first == key) {
            return prop.second;
        }
    }

    log.Warning("Properties::getString(" + key + ") : Key \"" + key + "\" not found in file \"" + file_path_ + "\".");
    throw read_property_exception("Properties::getString()", "Key \"" + key + "\" not found in file \"" + file_path_ + "\".");
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if read_property_exception is raised.
 * @return The value of the property as a string.
 */
const string properties::get_string(const string& key, const string& defaultValue)
{
    try {
        return get_string(key);
    } catch (const Exception& e) {
        log.Warning(e.simpleMessage() + " : Using default value \"" + defaultValue + "\".");
        return defaultValue;
    }
}

/**
 * Set the property value that matches the key.
 * @param key The key of the property.
 * @param value The value to set.
 * @throw read_property_exception if the key is not found.
 */
void properties::set_string(const string& key, const string& value)
{
    for (auto& prop : properties_) {
        if (prop.first == key) {
            prop.second = value;
            return;
        }
    }

    log.Warning("Properties::setString(), The key \"" + key + "\" does not exist in file \"" + file_path_ + "\".");
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as an integer.
 * @throw read_property_exception cast from string to int fails.
 */
const int properties::get_int(const string& key)
{
    auto propertyAsString = get_string(key);
    return stoi(propertyAsString);
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if read_property_exception is raised.
 * @return The value of the property as an integer.
 */
const int properties::get_int(const string& key, const int& defaultValue)
{
    try {
        return get_int(key);
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
void properties::set_int(const string& key, const int& value)
{
    set_string(key, to_string(value));
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as a long.
 * @throw read_property_exception cast from string to long fails.
 */
const long properties::get_long(const string& key)
{
    auto propertyAsString = get_string(key);
    return stol(propertyAsString);
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if read_property_exception is raised.
 * @return The value of the property as a long.
 */
const long properties::get_long(const string& key, const long& defaultValue)
{
    try {
        return get_long(key);
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
void properties::set_long(const string& key, const long& value)
{
    set_string(key, to_string(value));
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @return The value of the property as a boolean.
 */
const bool properties::get_bool(const string& key)
{
    auto string_property = get_string(key);
    if (string_property == "true") {
        return true;
    } else if (string_property == "false") {
        return false;
    }

    throw read_property_exception("Properties::getBool()", "Can not convert \"" + string_property + "\" to a boolean in file \"" + file_path_ + "\".");
}

/**
 * Get the property value that matches the key.
 * @param key The key of the property.
 * @param defaultValue The value to return if read_property_exception is raised.
 * @return The value of the property as a boolean.
 */
const bool properties::get_bool(const string& key, const bool& defaultValue)
{
    try {
        return get_bool(key);
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
void properties::set_bool(const string& key, const bool& value)
{
    const string valueAsString = (value) ? "true" : "false";
    set_string(key, valueAsString);
}

/**
 * Load the properties from a file.
 * @param path : The property file to read.
 */
void properties::load_properties(const string& path)
{
    file_handler fh(path, fh_open_mode::open_mode::read);
    if (!fh.get_file()) {
        throw load_property_exception("Properties::loadProperties()", "Can not open the file \"" + path + "\" to read !");
    }

    try {
        string line;
        while (getline(fh.get_file(), line)) {

            // Ignore empty lines and lines that begin with "#" (considered as comments)
            if (line.empty() || string_utils::starts_with(string_utils::trim(line), "#")) {
                continue;
            }

            const int equalPos = line.find('=');
            if (equalPos != string::npos) {
                const string key = string_utils::trim(line.substr(0, equalPos));
                const string value = string_utils::trim(line.substr(equalPos + 1));
                properties_[key] = value;
            }
        }
    } catch (const exception& e) {
        throw load_property_exception("Properties::loadProperties()", "An error occured while parsing the property file \"" + path + "\" : " + e.what());
    }
}

void properties::save_properties(const string& path)
{
    file_handler fh(path, fh_open_mode::open_mode::write);
    if (!fh.get_file()) {
        throw save_property_exception("Properties::saveProperties()", "Can not open the file \"" + path + "\" to write !");
    }

    try {
        for (const auto& prop : properties_) {
            fh.get_file() << prop.first << "=" << prop.second << endl;
        }
    } catch (const exception&) {
        throw save_property_exception("Properties::saveProperties()", "Error while saving the properties in the file \"" + path + "\".");
    }
}

void properties::save_properties()
{
    save_properties(file_path_);
}
