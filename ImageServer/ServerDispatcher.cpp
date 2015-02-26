#include "ServerDispatcher.h"

ServerDispatcher::ServerDispatcher() :m_imageResource(new ImagesResource()){
	init();
}

void ServerDispatcher::init() {

	m_registeredOperationsMap.insert(make_pair("http://localhost:2323/restdemo", std::tr1::bind(&ImagesResource::get,
		m_imageResource,
		std::tr1::placeholders::_1)));
	m_registeredOperations.insert(make_pair(ServerDataTypes::rest_methods::IGET, m_registeredOperationsMap));

}

CallBackOpeation  ServerDispatcher::getCallBack(ServerDataTypes::rest_operation operationType, string method) {
	CallBackMap mapofmap = m_registeredOperations.find(operationType)->second;
	map<string, CallBackOpeation>::iterator it;
	for (it = mapofmap.begin(); it != mapofmap.end(); it++) {
		string str = it->first;
		if (method.find(str) != string::npos)
			return it->second;
	}

}

ServerResponsePtr  ServerDispatcher::dispatch(ServerRequestPtr message) {
	CallBackOpeation operation = getCallBack(message->getMethod(), message->getUri());
	message->getJson();
	return operation(message);	
}



