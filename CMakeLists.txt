PROJECT( cpp_utils )
cmake_minimum_required(VERSION 3.0)

include(conanbuildinfo.cmake)
conan_basic_setup()

add_library(utils
		src/exception/config_exception.cpp
		src/exception/config_exception.h
		src/exception/Exception.cpp
		src/exception/Exception.h
		src/exception/file_exception.cpp
		src/exception/file_exception.h
		src/exception/property_exception.cpp
		src/exception/property_exception.h
		src/fs/file_handler.cpp
		src/fs/file_handler.h
		src/fs/fs_utils.cpp
		src/fs/fs_utils.h
		src/lang/lexicon.cpp
		src/lang/lexicon.h
		src/lang/lexicon_manager.cpp
		src/lang/lexicon_manager.h
		src/geometry.cpp
		src/geometry.h
		src/properties.cpp
		src/properties.h
		src/string_utils.cpp
		src/string_utils.h
		src/timer.cpp
		src/timer.h)
target_link_libraries(utils ${CONAN_LIBS})

IF(BUILD_TEST)
	add_executable(test_utils
			test/test_suites.cpp)
	target_link_libraries(test_utils utils ${CONAN_LIBS})
ENDIF()