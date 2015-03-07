#include "StorageUtils.h"
#include "StorageInterface.h"
#include "StorageFactory.h"
#include "ImageProcessor.h"

using namespace web;
using namespace concurrency::streams;
using namespace utility;
using namespace utility::conversions;  // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;


void StorageUtils::saveFile(ServerRequestPtr request) {
	StorageInterfacePtr storage = StorageFactory::getStorage();
	storage->writeFile(request);
}


json::value StorageUtils::getAllFiles(ServerRequestPtr request) {
	ImageProcessor imgProcessor;
	vector<wstring> imageList = imgProcessor.get_all_imagenames_from_dir(L"C:\\Personal");
	json::value json;

	std::vector<web::json::value> fileList;
	for (int i = 0; i < imageList.size(); i++)
	{
		web::json::value file;
		file[L"name"] = json::value::string(imageList[i]);
		fileList.push_back(file);
	}

	json[L"fileList"] = json::value::array(fileList);
	return json;
}

ServerResponsePtr StorageUtils::extractFile(ServerRequestPtr serverRequest) {

	http_request request = serverRequest->getRequest();
	string_t fileName_t = L"C:\\Personal\\";
	fileName_t += serverRequest->getFileName();	
	
	// Open file stream
	concurrency::streams::basic_istream<unsigned char> fileStream = file_stream<unsigned char>::open_istream(fileName_t).get();
	// Read file stream to string
	concurrency::streams::stringstreambuf streamBuffer;
	fileStream.read_to_end(streamBuffer).get();
	string textFile = move(streamBuffer.collection());
	fileStream.close();
	streamBuffer.close();

	// Make body text
	string textBoundary = "--0123456789";
	string textBody = "";

	textBody += textFile;

	// Put text to the buffer
	concurrency::streams::producer_consumer_buffer<unsigned char> buffer;
	buffer.putn((const unsigned char *)textBody.c_str(), textBody.length());
	buffer.close(std::ios_base::out);

	ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
	response->setBufferStream(buffer);
	response->setContentType(L"multipart/form-data");

	return response;
}

