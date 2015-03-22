#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "../src/fs/fs_utils.h"

		/**
		* Tests the Build a Path from a string.
		*/
		TEST(PathTest, FromString)
		{
			const std::string pathAsString = "C:\\toto\\titi\\tata\\";
            fs_utils::path pathFromString(pathAsString);

			const std::string expected	= pathAsString;
			const std::string actual		= pathFromString.to_string();

			EXPECT_EQ(expected, actual) << "PathAsString is not as expected.";
		}

		/**
		* Tests the Build a Path from a vector.
		*/
		TEST(PathTest, FromVector)
		{
std::vector<std::string> pathLevels = std::vector<std::string>();
			pathLevels.push_back("C:");
			pathLevels.push_back("toto");
			pathLevels.push_back("titi");
			pathLevels.push_back("tata");
            fs_utils::path pathFromLevel(pathLevels);

			const std::string expected	= "C:\\toto\\titi\\tata\\";
			const std::string actual		= pathFromLevel.to_string();

			EXPECT_EQ(expected, actual) << "pathFromLevel is not as expected.";
		}

		/**
		* Tests the current directory.
		*/
		TEST(PathTest, CurrentPath)
		{
			std::string path = fs_utils::get_current_directory();
			EXPECT_EQ(path, path) << "pathFromLevel is not as expected.";
		}