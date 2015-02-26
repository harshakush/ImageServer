#ifndef SERVER_REQUEST_HEADER
#define SERVER_REQUEST_HEADER
#include <memory>
#include <cpprest\asyncrt_utils.h>
#include <cpprest\http_headers.h>
#include <cpprest\http_msg.h>
#include "ServerDataTypes.h"
using namespace std;
using namespace web::http;

class ServerRequest {
public: ServerRequest(http_request message) : m_requestMessage(message) {
			
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

		web::json::value getJson() {
			m_jsonTask = m_requestMessage.extract_json();
			
			m_jsonRequest = m_jsonTask.get();
			return m_jsonRequest;
		}
private:
	const http_request m_requestMessage;
	web::json::value m_jsonRequest;
	pplx::task<web::json::value> m_jsonTask;
};
typedef shared_ptr<ServerRequest> ServerRequestPtr;
#endif