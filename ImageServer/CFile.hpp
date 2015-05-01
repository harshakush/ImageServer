
#ifndef CFILE_HEADER
#define CFILE_HEADER

#include <memory>
#include <iostream>
using namespace std;

class CFile {

public: 
	CFile() = default;

	CFile(wstring fileN, long fileS) :m_fileSize(fileS),m_fileName(fileN){
	}

	const wstring getFileName() const {
		return m_fileName;
	}

	long getFileSize() const {
		return m_fileSize;
	}

	CFile& fileName(wstring fileN) {
		m_fileName = fileN;
		return *this;
	}

	CFile& fileSize(long fileS) {
		m_fileSize = fileS;
		return *this;
	}

private:
	long m_fileSize;
	wstring m_fileName;

};


typedef shared_ptr<CFile> CFilePtr;

#endif