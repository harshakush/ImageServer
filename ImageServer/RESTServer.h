#ifndef REST_SERVER_HEADER
#define REST_SERVER_HEADER
#include <cpprest\http_listener.h>
#include <memory>
#include <cpprest\asyncrt_utils.h>
#include <cpprest\base_uri.h>
#include "ServerDispatcher.h"


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
	void handle_get(http_request message);
	void handle_put(http_request message);
	void handle_post(http_request message);
	void handle_delete(http_request message);

	http::uri m_uri;	
	http_listener m_listener;	
	ServerDispatcher m_dispatcher;
};

typedef shared_ptr<RestServer> RestSetbetListnerPtr;

#endif