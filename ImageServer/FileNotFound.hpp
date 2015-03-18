
#ifndef FILE_NOT_FOUND_HEADER
#define FILE_NOT_FOUND_HEADER

#include "RestServerException.h"

using namespace web;

class FileNotFoundException :public RestServerException {
public:
	FileNotFoundException(string_t fileName) : m_fileName(fileName) {
	}

	string_t what() {
		string_t error_message = ServerMessages::FILE_NOT_FOUND + m_fileName;
		return error_message;
	}

	virtual status_code getStatusCode() {
		return status_codes::NotFound;
	}

	string_t m_fileName;
};

#endif