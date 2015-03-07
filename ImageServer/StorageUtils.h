
#ifndef STORAGE_UTILS_HEADER
#define STORAGE_UTILS_HEADER

#include<iostream>
#include <memory>
#include<cpprest\http_msg.h>
#include "ServerRequest.h"
#include "ServerResponse.h"


using namespace std;
/*
Remove the server request object. These can be simple parameters.
we can make this code independent of http_request. Unnecessary reference.
*/

class StorageUtils {
public:
	static void saveFile(ServerRequestPtr request);
	static json::value getAllFiles(ServerRequestPtr request);
	static string_t getQueryParameter(http_request request);
	static ServerResponsePtr extractFile(ServerRequestPtr serverRequest);

};


#endif