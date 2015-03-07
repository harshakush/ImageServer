#include "RESTServer.h"
#include "ServerResponse.h"

void RestServer::handle_get(http_request message) {
	ServerRequestPtr request = ServerRequestPtr(new ServerRequest(message));	
	ServerResponsePtr responsePtr = m_dispatcher.dispatch(request);
	string_t fileName = request->getFileName();
	if (responsePtr->getBufferStream() != NULL) {

		/*message.get_response().then([fileName](http_response response) {
			response.headers().add(L"FileName", fileName);
		}
		); */
		//.add(L"FileName", request->getFileName());
		message.reply(status_codes::OK, responsePtr->getBufferStream(), responsePtr->getContenType());
	}
	else {
		
		message.reply(status_codes::OK, responsePtr->getResponse());
	}
}

void RestServer::handle_put(http_request message) {
	message.reply(status_codes::OK,
		m_dispatcher.dispatch(ServerRequestPtr(new ServerRequest(message)))->getResponse());
}
void RestServer::handle_post(http_request message) {
	message.reply(status_codes::OK,
		m_dispatcher.dispatch(ServerRequestPtr(new ServerRequest(message)))->getResponse());
}
void RestServer::handle_delete(http_request message) {
	message.reply(status_codes::OK,
		m_dispatcher.dispatch(ServerRequestPtr(new ServerRequest(message)))->getResponse());
}

void RestServer::start() {
	try {
		m_listener
			.open()
			.wait();

		Sleep(10000);
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
		std::tr1::bind(&RestServer::handle_delete,
		this,
		std::tr1::placeholders::_1));
}