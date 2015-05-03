#ifndef UNABLE_TO_READ_CONFIG
#define UNABLE_TO_READ_CONFIG

#include "RestServerException.h"
using namespace web;

class UnableToReadConfigException :public RestServerException {
public:
	
	UnableToReadConfigException()  {
	}

	wstring what() {

		return ServerMessages::CONFIG_ERROR;
	}

	virtual status_code getStatusCode() {
		return status_codes::ServiceUnavailable;
	}
};


#endif