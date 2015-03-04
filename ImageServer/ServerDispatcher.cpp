#include "ServerDispatcher.h"

RestInterfacePtr  ServerDispatcher::getRESTResource(ServerDataTypes::rest_operation operationType, string endpoint) {
	return m_resourceTable.getResource(endpoint);
}

ServerResponsePtr  ServerDispatcher::dispatch(ServerRequestPtr message) {
	RestInterfacePtr resource = getRESTResource(message->getMethod(), message->getUri());
	return resource->dispatch(message);	
}



