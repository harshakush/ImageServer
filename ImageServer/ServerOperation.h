#ifndef SERVER_UTILS_HEADER
#define SERVER_UTILS_HEADER

#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "pplx/pplxtasks.h"
#include<map>
#include<string>

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

	void register_operation(const http::method &operation_type, std::function<void()> operation) {
		m_registeredOperations.insert(make_pair(operation_type, operation));
	}

	function<void()> get_registered_operation(const http::method &operation_type) {
		return m_registeredOperations.find(operation_type)->second;
	}

private:

	std::map<const http::method, std::function<void()>> m_registeredOperations;

};

typedef shared_ptr<ServerOperation>  ServerOperationPtr;

#endif