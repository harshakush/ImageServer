
#ifndef FILE_NOT_FOUND_HEADER
#define FILE_NOT_FOUND_HEADER

#include "RestServerException.h"

using namespace web;

class FileNotFoundException :public RestServerException {
public:
	FileNotFoundException(wstring fileName) : m_fileName(fileName) {
	}

	wstring what() {
		wstring error_message = ServerMessages::FILE_NOT_FOUND + m_fileName;
		return error_message;
	}

	virtual status_code getStatusCode() {
		return status_codes::NotFound;
	}

	wstring m_fileName;
};

#endif