#include "StorageUtils.h"
#include "StorageInterface.h"
#include "StorageFactory.h"

void StorageUtils::saveFile(ServerRequestPtr request) {
	StorageInterfacePtr storage = StorageFactory::getStorage();
	storage->writeFile(request);
}

void StorageUtils::extractFile(ServerRequestPtr request) {

}