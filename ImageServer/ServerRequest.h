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
#include "ServerUtils.h"

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

	wstring getFileName() {
		return m_fileName;
	}

	wstring getRelativeUri() {
		return m_relative_formatted_uri;
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
		m_relative_uri = m_requestMessage.relative_uri();
		m_absolute_uri = m_requestMessage.absolute_uri();
		m_request_uri = m_requestMessage.request_uri();
		wstring query_param = ServerUtils::getQueryParameter(m_requestMessage);
		if (!query_param.empty()) {
			std::vector<unsigned char> base64_file_name = utility::conversions::from_base64(query_param);
			std::string str(base64_file_name.begin(), base64_file_name.end());
			m_fileName = ::conversions::to_string_t(str);			
		}
		m_relative_formatted_uri = ServerUtils::getRelativeUri(m_requestMessage);
	}



private:
	const http_request m_requestMessage;
	web::json::value m_jsonRequest;
	wstring m_fileName;
	wstring m_relative_formatted_uri;
	web::uri m_relative_uri;
	web::uri m_absolute_uri;
	web::uri m_request_uri;
};

typedef shared_ptr<ServerRequest> ServerRequestPtr;
#endif
