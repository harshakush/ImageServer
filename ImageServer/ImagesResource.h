
#ifndef IMAGES_RESOURCE_HEADER
#define IMAGES_RESOURCE_HEADER

#include "RestInterface.h"
#include "image_operations.h"
using namespace std;

class ImagesResource : public RestInterface {

private:
	ImageOperations m_ImgOperations;

public:
	ImagesResource() {

	}
	virtual ServerResponsePtr get(const ServerRequestPtr request){

		return m_ImgOperations.resizeImage(request);

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