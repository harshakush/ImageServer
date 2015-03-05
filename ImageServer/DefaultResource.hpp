#ifndef DEFAULT_RESOURCE_HEADER
#define DEFAULT_RESOURCE_HEADER

#include "RestInterface.h"
#include <memory>

using namespace std;
static const utf16string RESOURCE_NOT_FOUND = L"Resource not found";

class DefaultResource : public RestInterface {
public:
	DefaultResource() {
	}

	virtual ServerResponsePtr get(const ServerRequestPtr request){
		return ServerResponsePtr(new ServerResponse());
	}

	virtual ServerResponsePtr post(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse(RESOURCE_NOT_FOUND);
		return response;
	}
	virtual ServerResponsePtr put(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse(RESOURCE_NOT_FOUND);
		return response;
	}
	virtual ServerResponsePtr del(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse(RESOURCE_NOT_FOUND);
		return response;
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

typedef shared_ptr<DefaultResource> DefaultResourcePtr;
#endif