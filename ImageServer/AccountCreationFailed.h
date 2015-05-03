#ifndef ACCOUNT_CREATION_FAILED
#define ACCOUNT_CREATION_FAILED

#include "RestServerException.h"
#include <iostream>
using namespace web;

class AccountCreationFailed :public RestServerException {
public:
	AccountCreationFailed(wstring fileName)  {
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