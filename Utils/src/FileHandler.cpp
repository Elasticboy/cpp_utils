#include "StdAfx.h"
#include "FileHandler.h"

using namespace std;

FileHandler::FileHandler(const string& path, const int openType)
{
	if (openType == OPEN_TYPE_READ) {
		m_file.open(path.c_str(), ios::in);

	} else if (openType == OPEN_TYPE_WRITE) {
		m_file.open(path.c_str(), ios::out);

	} else if (openType == OPEN_TYPE_APPEND) {
		m_file.open(path.c_str(), ios::app);

	} else {
		throw OpenFileException();
	}
	
	if (!m_file.is_open()) {
		throw OpenFileException();
	}

	//cout << "File " << path << " is open !" << endl;
}

FileHandler::~FileHandler()
{
	if (m_file.is_open()) {
		m_file.close();
		//cout << "File has been closed !" << endl;
	}
}

fstream& FileHandler::getFile()
{
	return m_file;
}