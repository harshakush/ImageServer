#ifndef REST_SERVER_EXCEPTION_HEADER
#define REST_SERVER_EXCEPTION_HEADER

#include<cpprest\details\basic_types.h>
#include<cpprest\http_msg.h>
#include "ServerMessages.hpp"

//< Thought of extending this class from http_exception >>//
//< But that does not add any value >//
using namespace utility;
using namespace web::http;

class RestServerException :public std::exception {
public:
	virtual status_code getStatusCode() = 0;
	virtual string_t what() = 0;
};

#endif