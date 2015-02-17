#include "RESTServer.h"

void RestServer::handle_get(http_request message) {
	std::string uri = ::utility::conversions::to_utf8string(message.request_uri().to_string());
	m_dispatcher.dispatch(ServerDataTypes::rest_methods::IGET, uri);
	message.reply(status_codes::OK, U("Hello, World---23!"));
}

void RestServer::handle_put(http_request message) {
	message.reply(status_codes::OK, U("Hello, World---23!"));
}
void RestServer::handle_post(http_request message) {
	message.reply(status_codes::OK, U("Hello, World---23!"));
}
void RestServer::handle_delete(http_request message) {
	message.reply(status_codes::OK, U("Hello, World---23!"));
}

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


RestServer::RestServer(const http::uri& url) : m_listener(http_listener(url)), m_uri(url)
{

	//Have function pointer table and call them.
	//Ideally static method. Or else
	//A method parser which can be used.

	//testing push manu

	m_listener.support(methods::GET,
		std::tr1::bind(&RestServer::handle_get,
		this,
		std::tr1::placeholders::_1));

	m_listener.support(methods::PUT,
		std::tr1::bind(&RestServer::handle_put,
		this,
		std::tr1::placeholders::_1));
	m_listener.support(methods::POST,
		std::tr1::bind(&RestServer::handle_post,
		this,
		std::tr1::placeholders::_1));
	m_listener.support(methods::DEL,
		std::tr1::bind(&RestServer::handle_del,
		this,
		std::tr1::placeholders::_1));
}
