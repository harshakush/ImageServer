
#ifndef SERVER_RESPONSE_HEADER
#define SERVER_RESPONSE_HEADER

#include <memory>
#include <string>
#include "ServerDataTypes.h"
using namespace std;
using namespace web;
using namespace ServerDataTypes;

/// <This class has all response related methods>
/// <As of now json only>
/// <Stream need to be supported>

class ServerResponse {
public:

	ServerResponse() :m_contentType(L"application/json"), m_responseType(ServerDataTypes::ServerResponseType::JSON), m_statusCode(status_codes::OK){

	}

	void setResponseAsString(utf16string response) {
		m_response = response;
	}

	wstring getResponseAsString() {
		return m_response;
	}

	void setContentType(wstring contentType){
		m_contentType = contentType;
	}

	void setResponseType(ServerDataTypes::ServerResponseType type) {
		m_responseType = type;
	}

	wstring getContenType() {
		return m_contentType;
	}

	void setResponse(json::value json) {
		m_json = json;
	}

	const json::value getResponse() {
		return m_json;
	}


	ServerDataTypes::ServerResponseType getResponseType() {
		return m_responseType;
	}

	void setBufferStream(concurrency::streams::producer_consumer_buffer<unsigned char> buffer){
		m_buffer = buffer;
		m_responseType = ServerDataTypes::ServerResponseType::STREAM;
	}

	concurrency::streams::producer_consumer_buffer<unsigned char> getBufferStream() {
		return m_buffer;
	}

	void setStatusCode(status_code aStatusCode){
		m_statusCode = aStatusCode;
	}

	status_code getStatusCode(){
		return m_statusCode;
	}

private:
	utf16string m_response;
	json::value m_json;
	wstring m_contentType;
	concurrency::streams::producer_consumer_buffer<unsigned char> m_buffer;
	ServerResponseType m_responseType;
	status_code m_statusCode;
};
typedef shared_ptr<ServerResponse> ServerResponsePtr;

#endif