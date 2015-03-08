
#ifndef FILE_SYSTEMS_HEADER
#define FILE_SYSTEMS_HEADER

#include "StorageInterface.h"
#include "ImageProcessor.h"

using namespace web;
using namespace concurrency::streams;
using namespace utility;
using namespace utility::conversions;  // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;
using namespace std;

class FileSystemsStorage : public StorageInterface {

public:
	
	FileSystemsStorage() {

	}

	///< Make the destructor always virtual > ///
	virtual ~FileSystemsStorage() {

	}

	virtual json::value getAllFiles(ServerRequestPtr request, bool &);
	virtual void writeFile(ServerRequestPtr request);	
	virtual ServerResponsePtr readFile(ServerRequestPtr serverRequest);

	
};


#endif