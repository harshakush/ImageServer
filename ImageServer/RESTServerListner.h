#ifndef REST_SERVER_HEADER
#define REST_SERVER_HEADER
#include <cpprest\http_listener.h>
#include <memory>
#include "ServerOperation.h"

using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;
using namespace std;

class RestServer
{
public:
	RestServer(const http::uri& url);
	void start();
	void stop();

private:
	http::uri m_uri;
	ServerOperationPtr m_serverOperation;
	http_listener m_listener;	
};

typedef shared_ptr<RestServer> RestSetbetListnerPtr;

void RestServer::start() {
	try {
		m_listener
			.open()
			.wait();

	}
	catch (exception const &e){
		wcout << e.what() << endl;
	}
}

void RestServer::stop() {
	m_listener.close();
}


RestServer::RestServer(const http::uri& url) : m_listener(http_listener(url)), m_uri(url), m_serverOperation(new ServerOperation())
{

	//Have function pointer table and call them.
	//Ideally static method. Or else
	//A method parser which can be used.

	m_listener.support(methods::GET,
		std::tr1::bind(&ServerOperation::handle_get,
		m_serverOperation,
		std::tr1::placeholders::_1));

	 m_listener.support(methods::PUT,
		 std::tr1::bind(&ServerOperation::handle_get,
		 m_serverOperation,
		std::tr1::placeholders::_1));
	m_listener.support(methods::POST,
		std::tr1::bind(&ServerOperation::handle_get,
		m_serverOperation,
		std::tr1::placeholders::_1));
	m_listener.support(methods::DEL,
		std::tr1::bind(&ServerOperation::handle_get,
		m_serverOperation,
		std::tr1::placeholders::_1)); 
}
#endif