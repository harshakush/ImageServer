#ifndef ACCOUNT_ALREAY_EXISTS
#define ACCOUNT_ALREAY_EXISTS

#include "RestServerException.h"
#include <iostream>
using namespace web;

class AccountAlreadyExists :public RestServerException {
public:
	AccountAlreadyExists(wstring fileName)  {
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