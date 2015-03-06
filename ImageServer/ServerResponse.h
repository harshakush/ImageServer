
#ifndef SERVER_RESPONSE_HEADER
#define SERVER_RESPONSE_HEADER

#include <memory>
#include <string>
using namespace std;
using namespace web;

/// <This class has all response related methods>
/// <As of now json only>
/// <Stream need to be supported>

class ServerResponse {
public:
	ServerResponse() {

	}
	void setResponse(utf16string response) {
		m_response = response;		
	}
	void setContentType(string_t contentType){
		m_contentType= L"application/json";
	}

	void setResponse(json::value json) {
			m_json = json;
	}
	const json::value getResponse() {
		return m_json;
	}


	/* sample code.
	*/
	void buildJson() {
		m_json[L"key1"] = json::value::boolean(false);
		m_json[L"key2"] = json::value::number(44);
		m_json[L"key3"] = json::value::number(43.6);
		m_json[L"key4"] = json::value::string(U("str"));
	}

private :
	utf16string m_response;
	json::value m_json;
	string_t m_contentType;
};
typedef shared_ptr<ServerResponse> ServerResponsePtr;

#endif