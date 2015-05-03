#ifndef ACCOUNT_NOT_FOUND
#define ACCOUNT_NOT_FOUND

#include "RestServerException.h"
#include <iostream>
using namespace web;

class AccountNotFound :public RestServerException {
public:
	AccountNotFound(wstring fileName)  {
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