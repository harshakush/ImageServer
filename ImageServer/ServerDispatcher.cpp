#include "ServerDispatcher.h"

ServerDispatcher::ServerDispatcher() {
	init();
}

void ServerDispatcher::init() {
	RestInterfacePtr imageResource(new ImagesResource);
	m_registeredResources.insert(make_pair("http://localhost:2323/rest/images", imageResource));	

}

//Todo:
//Trie map
RestInterfacePtr  ServerDispatcher::getRESTResource(ServerDataTypes::rest_operation operationType, string endpoint) {
	map<string, RestInterfacePtr>::iterator it;
	for (it = m_registeredResources.begin(); it != m_registeredResources.end(); it++) {
		string str = it->first;
		if (endpoint.find(str) != string::npos)
			return it->second;
	}
	
}

ServerResponsePtr  ServerDispatcher::dispatch(ServerRequestPtr message) {
	RestInterfacePtr resource = getRESTResource(message->getMethod(), message->getUri());
	//message->getJson();
	return resource->dispatch(message);	
}



