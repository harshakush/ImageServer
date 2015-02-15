
#ifndef SERVER_DISPATCHER
#define SERVER_DISPATCHER

#include "ServerParameters.h"
#include "ServerOperation.h"
#include "ServerOperationType.h"
#include "ServerUtils.h"
#include "ServerOperationType.h"
#include <cpprest\http_msg.h>
#include<memory>

using namespace std;
using namespace web::http;

class ServerDispatcher {

private:
	// Move these as custom data types in
	// header file
	typedef std::function<void()> CallBack;
	typedef std::map<string, CallBack> RegisteredMultimap;

public:
	ServerDispatcher() {
		init();
	}
	CallBack  getCallBack(ServerOperationTypes::rest_operation operationType, string method) {
		RegisteredMultimap mapofmap = m_registeredOperations.find(operationType)->second;
		map<string, CallBack>::iterator it;
		for (it = mapofmap.begin(); it != mapofmap.end(); it++) {
			string str = it->first;
			if (method.find(str) != string::npos)
				return it->second;
		}
		
		//CallBack failed = std::bind(&ServerUtils::return_failed(), true);
		//failed = std::bind((void(Foo::*)(int, int))&Foo::foo, Foo(), 1, 2);
				
	}

	void  dispatch(ServerOperationTypes::rest_operation operationType, string method) {
		CallBack operation = getCallBack(operationType, method);
		operation();
	}
	
	void init() {
		//if (m_initalized) return;

		//m_initalized = true;
		m_registeredOperationsMap.insert(make_pair("http://localhost:2323/restdemo", ServerUtils::getRestDemo));
		m_registeredOperations.insert(make_pair(ServerOperationTypes::rest_methods::IGET, m_registeredOperationsMap));
	}

private:
	 RegisteredMultimap m_registeredOperationsMap;
	 std::map<ServerOperationTypes::rest_operation, RegisteredMultimap> m_registeredOperations;
	//static bool m_initalized;
	
};

typedef shared_ptr<ServerDispatcher> ServerDispatcherPtr;

#endif