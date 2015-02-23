
#ifndef SERVER_REQUEST_HEADER
#define SERVER_REQUEST_HEADER

#include <memory>
#include <cpprest\asyncrt_utils.h>
#include <cpprest\http_headers.h>
#include <cpprest\http_msg.h>

using namespace std;
using namespace web::http;

class ServerRequest {
public: ServerRequest(http_request message): m_requestMessage(message){

		}

		const http_request& getRequest() {
			return m_requestMessage;
		}

		string getUri() {
			return ::utility::conversions::to_utf8string(m_requestMessage.request_uri().to_string());
		}

		ServerDataTypes::rest_methods getMethod() {
			return ServerDataTypes::rest_methods::IGET;
		}

private:
	const http_request m_requestMessage;
};

typedef shared_ptr<ServerRequest> ServerRequestPtr;

#endif