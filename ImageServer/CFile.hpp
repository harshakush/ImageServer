
#ifndef CFILE_HEADER
#define CFILE_HEADER

#include <memory>
#include <iostream>
using namespace std;

class CFile {

public: 
	CFile(wstring fileN, long fileS) :m_fileSize(fileS),m_fileName(fileN){
		}

	wstring& getFileName() {
		return m_fileName;
	}

	long getFileSize() {
		return m_fileSize;
	}
private:

	long m_fileSize;
	wstring m_fileName;

};


typedef shared_ptr<CFile> CFilePtr;

#endif