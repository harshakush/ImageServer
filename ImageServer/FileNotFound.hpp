#include "RestServerException.h"

using namespace web;

class FileNotFoundException :public RestServerException {
public:
	FileNotFoundException(string_t fileName) : m_fileName(fileName) {
	}

	string_t what() {
		string_t error_message = L"File not found :"+ m_fileName;
		return error_message;
	}

	virtual status_code getStatusCode() {
		return status_codes::NoContent;
	}

	string_t m_fileName;
};
