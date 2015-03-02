
#ifndef STORAGE_UTILS_HEADER
#define STORAGE_UTILS_HEADER

#include<iostream>
#include <memory>
#include<cpprest\http_msg.h>
#include "ServerRequest.h"
#include "ServerResponse.h"


using namespace std;


class StorageUtils {
public:
	static void saveFile(ServerRequestPtr request);
	static void extractFile(ServerRequestPtr request);

};


#endif