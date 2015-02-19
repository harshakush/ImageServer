
#ifndef SERVER_DISPATCHER
#define SERVER_DISPATCHER

#include "ServerParameters.h"
#include "ServerDataTypes.h"
#include "ServerUtils.h"
#include "ServerRequest.h"
#include "ServerResponse.h"
#include "ImagesResource.h"
#include <cpprest\http_msg.h>
#include<memory>

using namespace std;
using namespace web::http;
using namespace ServerDataTypes;



//typedef function<void()> CallBackOpeation;
typedef function<ServerResponsePtr(ServerRequestPtr parameter)> CallBackOpeation;
typedef map<string, CallBackOpeation> CallBackMap;

class ServerDispatcher {

public:
	ServerDispatcher();
	
	CallBackOpeation  getCallBack(ServerDataTypes::rest_operation operationType, string method);

	ServerResponsePtr  dispatch(ServerDataTypes::rest_operation operationType, string method);
	
	void init();

private:
	CallBackMap m_registeredOperationsMap;
	std::map<ServerDataTypes::rest_operation, CallBackMap> m_registeredOperations;
	ImagesResource *m_imageResource;
	
};

typedef shared_ptr<ServerDispatcher> ServerDispatcherPtr;

#endif