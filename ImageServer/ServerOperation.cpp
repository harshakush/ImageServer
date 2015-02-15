
#include "ServerOperation.h"
#include <cpprest\asyncrt_utils.h>
#include <cpprest\base_uri.h>

using namespace utility::conversions;

ServerOperation::ServerOperation() {

}
void ServerOperation::handle_get(http_request message) {
	std::string uri = ::utility::conversions::to_utf8string(message.request_uri().to_string());
	m_dispatcher.dispatch(ServerOperationTypes::rest_methods::IGET, uri);
	message.reply(status_codes::OK, U("Hello, World---23!"));
}

void ServerOperation::handle_put(http_request message) {
	message.reply(status_codes::OK, U("Hello, World---23!"));
}
void ServerOperation::handle_post(http_request message) {
	message.reply(status_codes::OK, U("Hello, World---23!"));
}
void ServerOperation::handle_delete(http_request message) {
	message.reply(status_codes::OK, U("Hello, World---23!"));
}