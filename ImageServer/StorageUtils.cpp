#include "StorageUtils.h"
#include "StorageInterface.h"
#include "StorageFactory.h"
#include "ImageProcessor.h"

void StorageUtils::saveFile(ServerRequestPtr request) {
	StorageInterfacePtr storage = StorageFactory::getStorage();
	storage->writeFile(request);
}

void StorageUtils::extractFile(ServerRequestPtr request) {

}


json::value StorageUtils::getAllFiles(ServerRequestPtr request) {
	ImageProcessor imgProcessor;
	vector<wstring> imageList = imgProcessor.get_all_imagenames_from_dir(L"C:\\Personal");
	json::value json;

	std::vector<web::json::value> fileList;
	for (int i = 0; i < imageList.size(); i++)
	{
		web::json::value file;
		file[L"name"] = json::value::string(imageList[i]);
		fileList.push_back(file);
	}

	json[L"fileList"] = json::value::array(fileList);
	return json;
}