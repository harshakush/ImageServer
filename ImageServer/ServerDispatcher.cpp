#include "ServerDispatcher.h"

ServerDispatcher::ServerDispatcher() :m_imageResource(new ImagesResource()){
	init();
}

void ServerDispatcher::init() {

	CallBackMap registeredGetOperationsMap;
	registeredGetOperationsMap.insert(make_pair("http://localhost:2323/restdemo", std::tr1::bind(&ImagesResource::get,
		m_imageResource,
		std::tr1::placeholders::_1)));

	CallBackMap registeredPostOperationsMap;
	registeredGetOperationsMap.insert(make_pair("http://localhost:2323/restdemo", std::tr1::bind(&ImagesResource::post,
		m_imageResource,
		std::tr1::placeholders::_1)));

	//m_registeredOperations.insert(make_pair(ServerDataTypes::rest_methods::IGET, registeredGetOperationsMap));
	m_registeredOperations.insert(make_pair(ServerDataTypes::rest_methods::IPOST, registeredPostOperationsMap));

}

CallBackOpeation  ServerDispatcher::getCallBack(ServerDataTypes::rest_operation operationType, string method) {
	init();
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
	//message->getJson();
	//return operation(message);
	return m_imageResource->post(message);
}



