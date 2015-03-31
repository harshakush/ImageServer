#ifndef INVALID_REQ_HEADER
#define INVALID_REQ_HEADER

#include "RestServerException.h"
using namespace web;

class InvalidRequest :public RestServerException {
public:
	InvalidRequest(wstring fileName)  {
	}

	wstring what() {
		wstring error_message = ServerMessages::INVALID_URL;
		return error_message;
	}

	virtual status_code getStatusCode() {
		return status_codes::NoContent;
	}	
};


#endif