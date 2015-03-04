
#ifndef IMAGES_RESOURCE_HEADER
#define IMAGES_RESOURCE_HEADER

#include "RestInterface.h"
#include "StorageUtils.h"
using namespace std;


typedef function<ServerResponsePtr(ServerRequestPtr parameter)> CallBackOpeation;
class ImagesResource : public RestInterface {
public:
	ImagesResource() {
	}

	virtual ServerResponsePtr get(const ServerRequestPtr request){
		return ServerResponsePtr(new ServerResponse());
	}

	virtual ServerResponsePtr post(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		StorageUtils::saveFile(request);
		response->setResponse("file uploaded successfully");
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