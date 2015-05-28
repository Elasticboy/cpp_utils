#include "file_exception.h"

file_exception::file_exception(const std::string& source, const std::string& message)
        : Exception("file_exception", source, message) { }

open_file_exception::open_file_exception(const std::string& source, const std::string& message)
        : Exception("open_file_exception", source, message) { }

close_file_exception::close_file_exception(const std::string& source, const std::string& message)
        : Exception("close_file_exception", source, message) { }

read_file_exception::read_file_exception(const std::string& source, const std::string& message)
        : Exception("read_file_exception", source, message) { }

write_file_exception::write_file_exception(const std::string& source, const std::string& message)
        : Exception("write_file_exception", source, message) { }