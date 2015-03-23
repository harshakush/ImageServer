
#ifndef IMAGES_ACCOUNT_RESOURCE_HEADER
#define IMAGES_ACCOUNT_RESOURCE_HEADER

#include "RestInterface.h"


using namespace std;

static const utf16string RESOURCE_DEV = L"Resource not found";

class ImageAccountsResource : public RestInterface {
public:
	ImageAccountsResource() {
	}

	ServerResponsePtr prepareResponse() {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponseAsString(RESOURCE_DEV);
		response->setResponseType(ServerDataTypes::ServerResponseType::INVALID);
		response->setStatusCode(status_codes::NotFound);
		return response;
	}

	virtual ServerResponsePtr get(const ServerRequestPtr request){
		return prepareResponse();
	}

	virtual ServerResponsePtr post(const ServerRequestPtr request) {
		return prepareResponse();
	}

	virtual ServerResponsePtr put(const ServerRequestPtr request) {
		return prepareResponse();
	}

	virtual ServerResponsePtr del(const ServerRequestPtr request) {
		return prepareResponse();
	}

	virtual ServerResponsePtr dispatch(const ServerRequestPtr request) {
		if (request->getMethod() == ServerDataTypes::rest_methods::IGET) {
			return get(request);
		}
		else if (request->getMethod() == ServerDataTypes::rest_methods::IPOST) {
			return post(request);
		}
	}
};

#endif