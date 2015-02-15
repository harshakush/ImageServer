
#ifndef SERVER_DISPATCHER
#define SERVER_DISPATCHER

#include "ServerParameters.h"
#include "ServerOperation.h"

using namespace std;

class ServerDispatcher {

public: 
	void static dispatch(string method) {

	}

private:
	typedef std::map<string, std::function<void()>> RegisteredMultimap;
	RegisteredMultimap m_registeredOperationsMap;
	std::map<const http::method, RegisteredMultimap> m_registeredOperations;
};


#endif