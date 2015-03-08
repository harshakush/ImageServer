
#ifndef IMAGES_RESOURCE_HEADER
#define IMAGES_RESOURCE_HEADER

#include "RestInterface.h"
#include "StorageUtils.h"
#include "ImageProcessor.h"

using namespace std;


class ImagesResource : public RestInterface {
public:
	ImagesResource() {
	}

	virtual ServerResponsePtr get(const ServerRequestPtr request){
		if (request->getFileName().empty()) {
			bool bIsDirectoryEmpty = FALSE;
			ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
			response->setResponse(StorageUtils::getAllFiles(request, bIsDirectoryEmpty));
			if (bIsDirectoryEmpty)
			{
				response->setStatusCode(status_codes::NoContent);
			}
			return response;
		}
		return StorageUtils::extractFile(request);
		
	}

	virtual ServerResponsePtr post(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		StorageUtils::saveFile(request);
		response->setResponse(L"file uploaded successfully");
		return response;
	}
	virtual ServerResponsePtr put(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		StorageUtils::saveFile(request);
		response->setResponse(L"simple response");
		return response;
	}
	virtual ServerResponsePtr del(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		response->setResponse(L"simple response");
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