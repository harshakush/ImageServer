#include "RestServerException.h"


using namespace web;

class InvalidRequest :public RestServerException {
public:
	InvalidRequest(string_t fileName)  {
	}

	string_t what() {
		string_t error_message = ServerMessages::INVALID_URL;
		return error_message;
	}

	virtual status_code getStatusCode() {
		return status_codes::NoContent;
	}	
};
