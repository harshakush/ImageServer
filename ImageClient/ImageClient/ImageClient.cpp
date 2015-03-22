// ImageClient.cpp : Defines the entry point for the console application.
//

//Read the below link.
//We need to implememt it by ourself.
//http://casablanca.codeplex.com/discussions/452833
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include<cpprest\http_headers.h>
#include<cpprest\http_msg.h>
#include<cpprest\http_client.h>
#include<cpprest\rawptrstream.h> 
#include<cpprest\filestream.h>
#include <cpprest\asyncrt_utils.h>
#include<cpprest\producerconsumerstream.h>

#include <log4cplus/logger.h>
#include<log4cplus/fileappender.h>

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
//#include <iomanip>

//#pragma comment(lib, "log4cplusD")
using namespace log4cplus;

using namespace std;
using namespace web;
using namespace concurrency::streams;
using namespace utility;  
using namespace utility::conversions;  // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features


void DisplayJSONValue(json::value doc, vector<wstring> &fileList)
{
		for (auto& game : doc.at(U("fileList")).as_array())
		{
			for (auto& p : game.as_object())
			{
				string_t name = p.first;
				string_t value = p.second.as_string();
				wcout << name << L":" << value << endl;
				fileList.push_back(value);
					
			}
		}
}


// Retrieves a JSON value from an HTTP request.
pplx::task<void> getFileListAsync(bool display,vector<wstring> &returnList)
{
	// TODO: To successfully use this example, you must perform the request  
	// against a server that provides JSON data.  
	// This example fails because the returned Content-Type is text/html and not application/json.
	
	http_client client(L"http://localhost:6060/rest/images");
	return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
	{
		std::vector<web::json::value> arr;
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}
		else if (response.status_code() == status_codes::NoContent)
		{
			json::value obj;
			obj[L"StatusCode"] = json::value::string(U("204 No Content"));
			obj[L"ERROR"] = json::value::string(U("  Not found any images"));
			arr.push_back(obj);
			json::value jsonObjAsArray;
			jsonObjAsArray[L"fileList"] = json::value::array(arr);
			return pplx::task_from_result(jsonObjAsArray);
		}
		else if (response.status_code() == status_codes::NotFound)
		{
			json::value obj;
			obj[L"StatusCode"] = json::value::string(U("404 Not Found"));
			obj[L"ERROR"] = json::value::string(U(" Requested image could not be found"));
			arr.push_back(obj);
			json::value jsonObjAsArray;
			jsonObjAsArray[L"fileList"] = json::value::array(arr);
			return pplx::task_from_result(jsonObjAsArray);
		}
		// Handle error cases, for now return empty json value... 
		return pplx::task_from_result(json::value());
	})
		.then([&returnList,&display](pplx::task<json::value> previousTask)
	{
		try {
			const json::value& v = previousTask.get();				
			DisplayJSONValue(v, returnList);
		
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



pplx::task<void> downloadFileByName(const wstring &fileName) {

	wstring uri = L"http://localhost:6060/rest/images?fileName=";
	uri += fileName;
	http_client client(uri);
	wstring fileNameLocal(fileName.c_str());


	return client.request(methods::GET).then([fileNameLocal](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			//web::http::http_headers::const_iterator fileNameIter = response.headers().find(L"FileName");
			wstring fileToBeStored = L"C:\\downloaded\\" + fileNameLocal;
			//string_t fileToBeStored = utility::conversions::to_string_t(dirPath);
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
			catch (...) {
				wcout << L"Error downloading file" << endl;				
			}
		}

		return pplx::task_from_result(json::value());
	}).then([](pplx::task<json::value> previousTask)
	{
		try
		{
			const json::value& v = previousTask.get();
			vector<wstring> list;
			DisplayJSONValue(v, list);
		}
		catch (const http_exception& e)
		{
			// Print error.
			wostringstream ss;
			ss << e.what() << endl;
			wcout << ss.str();
		}
		catch (...) {
			//eat all
		}
	});
}


pplx::task<void> downloadFile() {
	wstring fileName;
	cout << "Enter the file to be downloaded" << endl;
	wcin >> fileName;
	return downloadFileByName(fileName);
}

pplx::task<void> uploadFile(string_t fileName_t) {

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
		catch (...) {
			//eat all
		}
		wstring responseBodyU = response.extract_string().get();
		string responseBody = utility::conversions::to_utf8string(responseBodyU);
		status_code responseStatus = response.status_code();
		cout << responseBody << "Response Code" << responseStatus << endl;
	});

}

void  uploadDirectory(string_t aPath) {

	vector<wstring> names;
	TCHAR search_path1[200];
	swprintf(search_path1, 200, L"%s\\*.*", aPath.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path1, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	for (wstring fileName : names) {
		uploadFile(aPath + L"\\" + fileName);
	}
}

std::vector<wstring> getFileListFromDirectory(wstring dir) {
	vector<wstring> names;
	TCHAR search_path1[200];
	swprintf(search_path1, 200, L"%s\\*.*", dir.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path1, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

std::vector<wstring> getFileList(json::value doc) {
	std::vector<wstring> fileList;
	for (auto& game : doc.at(U("fileList")).as_array()) {
		for (auto& p : game.as_object()) {
			string_t name = p.first;
			string_t value = p.second.as_string();
			fileList.push_back(value);
		}
	}

	return fileList;
}

void sync() {
	vector<wstring> downloadedFiles = getFileListFromDirectory(L"C:\\downloaded\\");
	vector<wstring> fileListInServer;
	getFileListAsync(false, fileListInServer).wait();

	//upload
	for (wstring fileNme : downloadedFiles) {		
		if (std::find(fileListInServer.begin(), fileListInServer.end(), fileNme) == fileListInServer.end()) {		

			try {
				uploadFile(L"C:\\downloaded\\"+fileNme);
			}
			catch (exception &e){

			}
			catch (...) {

			}
		}	
	}

	//download
	for (wstring fileNme : fileListInServer) {
		if (std::find(downloadedFiles.begin(), downloadedFiles.end(), fileNme) == downloadedFiles.end()) {			
			try {
				downloadFileByName(fileNme);
			}
			catch (exception &e){

			}
			catch (...) {

			}
		}
	}
	
	cout << " Sync will be completed, all requests pooled" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	PropertyConfigurator config(U("logs.properties"));
	config.configure();
	Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("_tmain"));
	LOG4CPLUS_WARN(logger, "Hello, World!");
	vector<wstring> listOfFiles;
	
	while (1) {
		int input;
		string_t fileName_t;

		cout << "==========            Image Client - v1.0           ==========="<<endl;
		cout << "==========            Please enter                  ==========="<<endl;
		cout << "==========       1 for Get the file list            ==========="<<endl;
		cout << "==========       2 for Uploading file               ==========="<<endl;
		cout << "==========       3 for Downloading file             ==========="<<endl;
		cout << "==========       4 for Uploading directory          ==========="<<endl;
		cout << "==========       5 for Sync                         ==========="<<endl;
		cin >> input;


		switch (input) {

		case 1:			
			getFileListAsync(true, listOfFiles);
			break;
		case 2:
			cout << "Enter the file to be uploaded to server\n";
			wcin >> fileName_t;
			uploadFile(fileName_t);
			break;
		case 3:
			downloadFile();
			break;
		case 4:
			cout << "Enter the directory to upload";
			wcin >> fileName_t;
			uploadDirectory(fileName_t);
			break;
		case 5:
			cout << " Sync in progress...." << endl;
			sync();
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

