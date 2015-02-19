
#ifndef IMAGES_RESOURCE_HEADER
#define IMAGES_RESOURCE_HEADER

#include "RestInterface.h"
using namespace std;

class ImagesResource : public RestInterface {

public:
	ImagesResource() {

	}
	virtual ServerResponsePtr get(const ServerRequestPtr request){
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse("simple response");
		return response;

	}
	virtual ServerResponsePtr post(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse("simple response");
		return response;
	}
	virtual ServerResponsePtr put(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse("simple response");
		return response;
	}
	virtual ServerResponsePtr del(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse("simple response");
		return response;
	}
};

#endif