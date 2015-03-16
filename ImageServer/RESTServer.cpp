#include "RESTServer.h"
#include "ServerResponse.h"

void RestServer::handle_get(http_request message) {

	ServerRequestPtr request = ServerRequestPtr(new ServerRequest(message));	

	try {

		ServerResponsePtr responsePtr = m_dispatcher.dispatch(request);
		
		switch (responsePtr->getResponseType()) {
		case ServerResponseType::STREAM:
			message.reply(responsePtr->getStatusCode(), responsePtr->getBufferStream(), responsePtr->getContenType());
			break;
		case ServerResponseType::JSON:
			message.reply(responsePtr->getStatusCode(), responsePtr->getResponse());
			break;

		case ServerResponseType::PLAIN_TEXT:
			message.reply(responsePtr->getStatusCode(), responsePtr->getResponseAsString());
			break;

		default:
			message.reply(responsePtr->getStatusCode(), responsePtr->getResponseAsString());

		}
	}
	//<Catch all the application defined exceptions here>//
	catch (http_exception &e){
		message.reply(status_codes::InternalError, e.what());
	}
	catch (exception &e) {
		message.reply(status_codes::InternalError, L"Some Internal error occured");
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