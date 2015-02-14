
#include "ServerOperation.h"

ServerOperation::ServerOperation()
{

}
void ServerOperation::handle_get(http_request message) {
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