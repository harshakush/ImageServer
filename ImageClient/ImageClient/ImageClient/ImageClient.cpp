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



int _tmain(int argc, _TCHAR* argv[])
{
	string fileName = "Harsha.txt";
	string filePath = "C:\\Harsha.txt";

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

	// Note: form data and content type depend on your application
	textBody += "--" + textBoundary + "\r\n";
	textBody += "Content-Disposition: form-data; name=\"file[]\"; filename=\"" + fileName + "\"\r\n";
	textBody += "Content-Type: application/octet-stream\r\n\r\n";
	textBody += textFile + "\r\n";

	// Last boundary
	textBody += "--" + textBoundary + "--\r\n";

	// Put text to the buffer
	concurrency::streams::producer_consumer_buffer<unsigned char> buffer;
	buffer.putn((const unsigned char *)textBody.c_str(), textBody.length());
	buffer.close(std::ios_base::out);

	// Set website
	string_t website = L"http://localhost:2323/restdemo";
	http_client client(website);

	// Create HTTP request
	http_request msg;
	msg.set_body(concurrency::streams::istream(buffer));
	msg.set_method(methods::POST);
	msg.headers().set_content_type(to_string_t("multipart/form-data; boundary=" + textBoundary));
	msg.headers().set_content_length(textBody.length());

	// Send HTTP request
	http_response response = client.request(msg).get();
	return 0;
}

