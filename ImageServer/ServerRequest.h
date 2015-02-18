
#ifndef SERVER_REQUEST_HEADER
#define SERVER_REQUEST_HEADER

#include <memory>
using namespace std;

class ServerRequest {
public: ServerRequest() {

		}


};

typedef shared_ptr<ServerRequest> ServerRequestPtr;

#endif