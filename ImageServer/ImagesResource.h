
#ifndef IMAGES_RESOURCE_HEADER
#define IMAGES_RESOURCE_HEADER

#include "RestInterface.h"
#include "image_operations.h"
#include "StorageUtils.h"
using namespace std;

//Todo : Maintain the same function pointer map
//and automate the dispatch

//resource images:
typedef function<ServerResponsePtr(ServerRequestPtr parameter)> CallBackOpeation;
class ImagesResource : public RestInterface {

private:
	ImageOperations m_ImgOperations;

public:
	ImagesResource() {

		/* m_registeredResources.insert(make_pair(ServerDataTypes::rest_methods::IGET, std::tr1::bind(&ImagesResource::get,
			this,
			std::tr1::placeholders::_1))); */
	}

	virtual ServerResponsePtr get(const ServerRequestPtr request){
		return m_ImgOperations.resizeImage(request);
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
		//CallBackOpeation operation = m_registeredResources.find(request->getMethod());
		//return operation(request);

		if (request->getMethod() == ServerDataTypes::rest_methods::IGET) {
			return get(request);
		}

		else if (request->getMethod() == ServerDataTypes::rest_methods::IPOST) {
			return post(request);
		}
	}
private:
	//std::map<ServerDataTypes::rest_methods, CallBackOpeation> m_registeredResources;

};

#endif