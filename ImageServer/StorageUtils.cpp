#include "StorageUtils.h"
#include "StorageInterface.h"
#include "StorageFactory.h"



void StorageUtils::saveFile(ServerRequestPtr request) {
	StorageInterfacePtr storage = StorageFactory::getStorage();
	storage->writeFile(request);
}


json::value StorageUtils::getAllFiles(ServerRequestPtr request, bool & bIsDirectoryEmpty) {
	StorageInterfacePtr storage = StorageFactory::getStorage();
	return storage->getAllFiles(request, bIsDirectoryEmpty);
}

ServerResponsePtr StorageUtils::extractFile(ServerRequestPtr request) {
	StorageInterfacePtr storage = StorageFactory::getStorage();
	return storage->readFile(request);
}

