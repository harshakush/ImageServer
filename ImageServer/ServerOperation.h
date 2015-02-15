#ifndef SERVER_UTILS_HEADER
#define SERVER_UTILS_HEADER

#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "pplx/pplxtasks.h"
#include<map>
#include<string>
#include "ServerDispatcher.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace std;

class ServerOperation {
	
public:
	ServerOperation();

	void handle_get(http_request message);
	void handle_put(http_request message);
	void handle_post(http_request message);
	void handle_delete(http_request message);

private:
	ServerDispatcher m_dispatcher;

};

typedef shared_ptr<ServerOperation>  ServerOperationPtr;

#endif