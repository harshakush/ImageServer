// ImageClient.cpp : Defines the entry point for the console application.
//

//Read the below link.
//We need to implememt it by ourself.
//http://casablanca.codeplex.com/discussions/452833
#include "stdafx.h"
#include <iostream>
#include<cpprest\http_headers.h>
#include<cpprest\http_msg.h>
#include<cpprest\http_client.h>
#include<cpprest\rawptrstream.h> 
#include<cpprest\filestream.h>
#include <cpprest\asyncrt_utils.h>
#include<cpprest\producerconsumerstream.h>

using namespace std;
using namespace web;
using namespace concurrency::streams;
using namespace utility;  
using namespace utility::conversions;  // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features


void DisplayJSONValue(json::value doc)
{
	for (auto& game : doc.at(U("fileList")).as_array())
	{
		for (auto& p : game.as_object())
		{
			string_t name = p.first;
			string_t value = p.second.as_string();
			wcout << name << L":" << value << endl;
				
		}
	}
}


// Retrieves a JSON value from an HTTP request.
pplx::task<void> RequestJSONValueAsync()
{
	// TODO: To successfully use this example, you must perform the request  
	// against a server that provides JSON data.  
	// This example fails because the returned Content-Type is text/html and not application/json.
	http_client client(L"http://localhost:6060/rest/images");
	return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}

		// Handle error cases, for now return empty json value... 
		return pplx::task_from_result(json::value());
	})
		.then([](pplx::task<json::value> previousTask)
	{
		try
		{
			const json::value& v = previousTask.get();			
			DisplayJSONValue(v);
		}
		catch (const http_exception& e)
		{
			// Print error.
			wostringstream ss;
			ss << e.what() << endl;
			wcout << ss.str();
		}
	});

	/* Output:
	Content-Type must be application/json to extract (is: text/html)
	*/
}

pplx::task<void> downloadFile()
{

		// TODO: To successfully use this example, you must perform the request  
	// against a server that provides JSON data.  
	// This example fails because the returned Content-Type is text/html and not application/json.

	string fileName;
	cout << "Enter the file to be downloaded" << endl;
	cin >> fileName;

	string uri = "http://localhost:6060/rest/images?fileName=";
	uri += fileName;
	string_t uri_t = utility::conversions::to_string_t(uri);
	http_client client(uri_t);

	return client.request(methods::GET).then([fileName](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			//web::http::http_headers::const_iterator fileNameIter = response.headers().find(L"FileName");
			string dirPath = "C:\\downloaded\\" + fileName;
			string_t fileToBeStored = utility::conversions::to_string_t(dirPath);
			try {
				auto stream = concurrency::streams::fstream::open_ostream(
					fileToBeStored,
					std::ios_base::out | std::ios_base::binary).get();
				response.body().read_to_end(stream.streambuf()).wait();
				stream.close().get();
			}
			catch (exception &e) {
				wcout << L"Error downloading file" << endl;
				wcout << e.what();
			}
			}

		return pplx::task_from_result(json::value());	
	}).then([](pplx::task<json::value> previousTask)
	{
		try
		{
			const json::value& v = previousTask.get();
			DisplayJSONValue(v);
		}
		catch (const http_exception& e)
		{
			// Print error.
			wostringstream ss;
			ss << e.what() << endl;
			wcout << ss.str();
		}
	});

	/* Output:
	Content-Type must be application/json to extract (is: text/html)
	*/
}



pplx::task<void> uploadFile() {
	string fileName = "Harsha.jpg";
	string filePath = "C:\\Harsha.jpg";

	string_t fileName_t;//to_string_t(const std::string &s)

	cout << "Enter the file to be uploaded to server\n";
	cin >> filePath;
	fileName_t = to_string_t(filePath);


	// Open file stream
	concurrency::streams::basic_istream<unsigned char> fileStream = file_stream<unsigned char>::open_istream(to_string_t(filePath)).get();

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

	// Set website
	string_t website = L"http://localhost:6060/rest/images";
	http_client client(website);

	// Create HTTP request
	http_request msg;
	msg.set_body(concurrency::streams::istream(buffer));
	msg.set_method(methods::POST);
	msg.headers().set_content_type(to_string_t("multipart/form-data; boundary=" + textBoundary));
	msg.headers().set_content_length(textBody.length());
	msg.headers().add(L"FileName", fileName_t);
	//msg.headers().add(L"FileSize", textBody.length());

	// Send HTTP request

	return client.request(msg).then([](pplx::task<http_response> responseTask)
	{
		http_response response;
		try
		{
			response = responseTask.get();
		}
		catch (http_exception & e)
		{
			wcout << e.what() << endl;
		}
		wstring responseBodyU = response.extract_string().get();
		string responseBody = utility::conversions::to_utf8string(responseBodyU);
		status_code responseStatus = response.status_code();
		cout << responseBody << "Response Code" << responseStatus << endl;
	});

}

int _tmain(int argc, _TCHAR* argv[])
{

	while (1) {
		int input;
		cout << "Please enter 1 for get and 2 for post 3 for download";
		cin >> input;

		switch (input) {

		case 1: 
			RequestJSONValueAsync().wait();
			break;
		case 2: uploadFile().wait();
			break;
		case 3:
			downloadFile();
			break;
		}
		
		cout << "Do you want to continue ? \n";

		char yes;
		cin >> yes;

		if (yes == 'y' || yes == 'Y') {
		continue;
		}
		else {
		break;
		}
	}
	return 0;
}

