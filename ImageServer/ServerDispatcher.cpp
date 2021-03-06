#include "ServerDispatcher.h"

RestInterfacePtr  ServerDispatcher::getRESTResource(ServerDataTypes::rest_operation operationType, wstring endpoint) {
	return m_resourceTable.getResource(endpoint);
}

ServerResponsePtr  ServerDispatcher::dispatch(ServerRequestPtr message) {
	RestInterfacePtr resource = getRESTResource(message->getMethod(), message->getRelativeUri());
	return resource->dispatch(message);
}



