#include<cpprest\details\basic_types.h>
#include<cpprest\http_msg.h>

using namespace utility;
using namespace web::http;

class RestServerException :public std::exception {
public:
	virtual status_code getStatusCode() = 0;
	virtual string_t what() = 0;
};
