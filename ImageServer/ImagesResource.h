
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
		ServerResponsePtr respone = ServerResponsePtr(new ServerResponse());
		ImageProcessor imgProcessor;
		vector<wstring> imageList= imgProcessor.get_all_imagenames_from_dir(L"C:\\Personal");
		json::value json; 
	
		std::vector<web::json::value> fileList;
		for (int i = 0; i < imageList.size(); i++)
		{
			web::json::value file;		
			file[L"name"] = json::value::string(imageList[i]);
			fileList.push_back(file);
		}

		json[L"fileList"] = json::value::array(fileList);
		respone->setResponse(json);
		return respone;
	}

	virtual ServerResponsePtr post(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
		StorageUtils::saveFile(request);
		response->setResponse(L"file uploaded successfully");
		return response;
	}
	virtual ServerResponsePtr put(const ServerRequestPtr request) {
		ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
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