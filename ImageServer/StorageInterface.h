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

	virtual void writeFile(ServerRequestPtr request) = 0;
	virtual void readFile(ServerRequestPtr request) = 0;
	
	virtual ~StorageInterface() {

	}

};
typedef shared_ptr<StorageInterface> StorageInterfacePtr;

#endif