#include "ServerDispatcher.h"
#include "ServerDataTypes.h"

ServerDispatcher::ServerDispatcher() {
	init();
}

void ServerDispatcher::init() {
	m_registeredOperationsMap.insert(make_pair("http://localhost:2323/restdemo", ServerUtils::getRestDemo));
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

void  ServerDispatcher::dispatch(ServerDataTypes::rest_operation operationType, string method) {
	CallBackOpeation operation = getCallBack(operationType, method);
	operation();
}



