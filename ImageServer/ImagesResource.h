
#ifndef IMAGES_RESOURCE_HEADER
#define IMAGES_RESOURCE_HEADER

#include "RestInterface.h"
using namespace std;
class ImagesResource : public RestInterface {

public:
	virtual ServerResponsePtr get(const ServerRequestPtr request){
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse("simple response");

	}
	virtual ServerResponsePtr post(const ServerRequestPtr request) {

	}
	virtual ServerResponsePtr put(const ServerRequestPtr request) {

	}
	virtual ServerResponsePtr del(const ServerRequestPtr request) {

	}
};

#endif