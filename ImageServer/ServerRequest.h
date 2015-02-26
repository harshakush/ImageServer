#ifndef SERVER_REQUEST_HEADER
#define SERVER_REQUEST_HEADER
#include <memory>
#include <cpprest\asyncrt_utils.h>
#include <cpprest\http_headers.h>
#include <cpprest\http_msg.h>
using namespace std;
using namespace web::http;

class ServerRequest {

public: 
	ServerRequest(http_request message) : m_requestMessage(message) {
		init();
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
		return m_jsonRequest;
	}
private:
	void init() {
		web::json::value answer;
		m_requestMessage.extract_json().then([&answer](pplx::task<web::json::value> task) {
			try {
				answer = task.get();
			}
			catch (http_exception const & e)
			{
				wcout << e.what() << endl;
			}
		})
			.wait();
		//this wait here makes it synchronous
		m_jsonRequest = answer;
	}

	const http_request m_requestMessage;
	web::json::value m_jsonRequest;
};

typedef shared_ptr<ServerRequest> ServerRequestPtr;
#endif
