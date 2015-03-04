
#ifndef SERVER_DISPATCHER
#define SERVER_DISPATCHER

#include "ServerParameters.h"
#include "ServerDataTypes.h"
#include "ServerUtils.h"
#include "ServerRequest.h"
#include "ServerResponse.h"
#include "ImagesResource.h"
#include "ResourceTable.hpp"
#include <cpprest\http_msg.h>
#include<memory>

using namespace std;
using namespace web::http;
using namespace ServerDataTypes;


class ServerDispatcher {

public:
	ServerDispatcher() {

	}
	RestInterfacePtr  getRESTResource(ServerDataTypes::rest_operation operationType, string method);

	ServerResponsePtr  dispatch(ServerRequestPtr request);
	
private:
	ResourceTable m_resourceTable;	
};

typedef shared_ptr<ServerDispatcher> ServerDispatcherPtr;

#endif