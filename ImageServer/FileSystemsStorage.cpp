
#include "FileSystemsStorage.h"


json::value FileSystemsStorage::getAllFiles(ServerRequestPtr request) {
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
 void FileSystemsStorage::writeFile(ServerRequestPtr request)  {

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

 ServerResponsePtr FileSystemsStorage::readFile(ServerRequestPtr serverRequest)  {

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

