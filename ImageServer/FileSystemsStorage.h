
#ifndef FILE_SYSTEMS_HEADER
#define FILE_SYSTEMS_HEADER

#include "StorageInterface.h"

using namespace std;

class FileSystemsStorage : public StorageInterface {

public:
	FileSystemsStorage() {

	}

	virtual void writeFile(ServerRequestPtr request)  {

		//Move all the details to some util file.
		web::http::http_headers::const_iterator fileName = request->getRequest().headers().find(L"FileName");
		char path[_MAX_PATH];
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char name[_MAX_FNAME];
		char ext[_MAX_EXT];
		_bstr_t b(fileName->second.c_str());
		const char* c = b;

		_splitpath(c, drive, path, name, ext);

		string str(name);
		string fullPath = "C:\\Personal\\" + str + ext;
		string_t fileToBeStored = utility::conversions::to_string_t(fullPath);
		auto stream = concurrency::streams::fstream::open_ostream(
			fileToBeStored,
			std::ios_base::out | std::ios_base::binary).get();
		request->getRequest().body().read_to_end(stream.streambuf()).wait();
		stream.close().get();
	}
	
	virtual void readFile(ServerRequestPtr request)  {

	}

	virtual ~FileSystemsStorage() {

	}

};


#endif