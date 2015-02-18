
#ifndef SERVER_RESPONSE_HEADER
#define SERVER_RESPONSE_HEADER

#include <memory>
using namespace std;

class ServerResponse {
public:
	ServerResponse() {

	}


};
typedef shared_ptr<ServerResponse> ServerResponsePtr;

#endif