
#ifndef SERVER_RESPONSE_HEADER
#define SERVER_RESPONSE_HEADER

#include <memory>
#include <string>
using namespace std;

class ServerResponse {
public:
	ServerResponse() {
	}
	void setResponse(string response) {
		m_response = response;
	}

	string getResponse() {
		return m_response;
	}
private :
	string m_response;
};
typedef shared_ptr<ServerResponse> ServerResponsePtr;

#endif