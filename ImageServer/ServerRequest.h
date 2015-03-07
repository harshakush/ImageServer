#ifndef SERVER_REQUEST_HEADER
#define SERVER_REQUEST_HEADER
#include <memory>
#include <comdef.h> 

#include <cpprest\asyncrt_utils.h>
#include <cpprest\http_headers.h>
#include <cpprest\http_msg.h>
#include<cpprest\rawptrstream.h> 
#include<cpprest\filestream.h>
#include <cpprest\asyncrt_utils.h>
#include<cpprest\producerconsumerstream.h>

#include "ServerDataTypes.h"

using namespace std;
using namespace web::http;
using namespace concurrency::streams;
using namespace utility;

class ServerRequest {

public: 
	ServerRequest(http_request message) : m_requestMessage(message), m_fileName(L""){
		init();
	}

	const http_request& getRequest() {
		return m_requestMessage;
	}

	string getUri() {
		return ::utility::conversions::to_utf8string(m_requestMessage.request_uri().to_string());
	}

	ServerDataTypes::rest_methods getMethod() {
		if (m_requestMessage.method() == web::http::methods::GET){
			return ServerDataTypes::rest_methods::IGET;
		}
		else if (m_requestMessage.method() == web::http::methods::POST) {
			return ServerDataTypes::rest_methods::IPOST;
		}
		return ServerDataTypes::rest_methods::IGET;
	}

	web::json::value getJson() {
		return m_jsonRequest;
	}

	void extractString() {

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

		web::uri relative_uri_p = m_requestMessage.relative_uri();
		web::uri absolute_uri_p = m_requestMessage.absolute_uri();
		web::uri request_uri_p = m_requestMessage.request_uri();
		string_t queryParameters = relative_uri_p.query();

		string_t code;
		if (queryParameters.find(L"="))		{
			
			string_t name = queryParameters.substr(0, queryParameters.find(L"="));
			m_fileName = queryParameters.substr(queryParameters.find(L"=") + 1, queryParameters.size() - 1);
		}	
				
	}

	string_t getFileName() {
		return m_fileName;
	}

	const http_request m_requestMessage;
	web::json::value m_jsonRequest;
	string_t m_fileName;
	
};

typedef shared_ptr<ServerRequest> ServerRequestPtr;
#endif
