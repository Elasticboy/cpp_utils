#pragma once

#include <string>
#include <map>

#include "fs/file_handler.h"

class properties
{
public:
    properties(const std::string& path);

protected:
    void load_properties(const std::string& path);

    void save_properties(const std::string& path);

    void save_properties();

    const std::string get_string(const std::string& key);

    const std::string get_string(const std::string& key, const std::string& default_value);

    void set_string(const std::string& key, const std::string& value);

    const int get_int(const std::string& key);

    const int get_int(const std::string& key, const int& default_value);

    void set_int(const std::string& key, const int& value);

    const long get_long(const std::string& key);

    const long get_long(const std::string& key, const long& default_value);

    void set_long(const std::string& key, const long& value);

    const bool get_bool(const std::string& key);

    const bool get_bool(const std::string& key, const bool& default_value);

    void set_bool(const std::string& key, const bool& value);

    const std::map <std::string, std::string> get_list() const { return properties_; }

    const std::string get_file_path() const { return file_path_; }

private:
    std::map <std::string, std::string> properties_;
    std::string file_path_;
};