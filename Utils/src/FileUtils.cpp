#include "stdafx.h"
#include "FileUtils.h"

using namespace std;

vector<string> FileUtils::listFiles(const string& directory)
{
	// Prepare string to use FindFile function
	// Add "\\*" to the end of the path.
	string searchPath = directory + "\\*";
	// TODO: To be continued...
}
