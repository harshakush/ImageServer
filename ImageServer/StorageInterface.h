/* 
* Defines the basic storage inteface
* Will be extended once things are clear.
*/

#ifndef STORAGE_INTERFACE_HDR
#define STORAGE_INTERFACE_HDR
#include "ServerRequest.h"
#include "ServerResponse.h"
#include <memory>

class StorageInterface {

public:
	virtual ~StorageInterface() {

	}
	virtual void writeFile(ServerRequestPtr request) = 0;
	virtual ServerResponsePtr readFile(ServerRequestPtr request) = 0;
	virtual json::value getAllFiles(ServerRequestPtr request) = 0;

};
typedef shared_ptr<StorageInterface> StorageInterfacePtr;

#endif