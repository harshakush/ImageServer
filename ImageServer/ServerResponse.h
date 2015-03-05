
#ifndef SERVER_RESPONSE_HEADER
#define SERVER_RESPONSE_HEADER

#include <memory>
#include <string>
using namespace std;
using namespace web;

class ServerResponse {
public:
	ServerResponse() {
	}
	void setResponse(utf16string response) {
		m_response = response;
		//buildJson();
	}

	const json::value getResponse() {
		buildJson();
		return m_json;
	}


	void buildJson() {
		m_json[L"key1"] = json::value::boolean(false);
		m_json[L"key2"] = json::value::number(44);
		m_json[L"key3"] = json::value::number(43.6);
		m_json[L"key4"] = json::value::string(U("str"));
	}

private :
	utf16string m_response;
	json::value m_json;
};
typedef shared_ptr<ServerResponse> ServerResponsePtr;

#endif