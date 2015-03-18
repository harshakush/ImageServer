#ifndef SERVER_UTILS
#define SERVER_UTILS

#include<iostream>

#include<Windows.h>
#include<Pathcch.h>
#include <cpprest\asyncrt_utils.h>
#include <cpprest\http_headers.h>
#include <cpprest\http_msg.h>
#include<cpprest\rawptrstream.h> 
#include<cpprest\filestream.h>
#include <cpprest\asyncrt_utils.h>
#include<cpprest\producerconsumerstream.h>

#include <stdio.h> 
#include <direct.h>
#include <sys/stat.h>

#define GetCurrentDir _getcwd


using namespace std;
using namespace web::http;
using namespace concurrency::streams;
using namespace utility;

class ServerUtils
{
public:
	// <this will return map, will be done when required.>//
	static string_t getQueryParameter(http_request request){
		string_t queryParameter = request.relative_uri().query();

		if (queryParameter.find(L"=")) {
			string_t name = queryParameter.substr(0, queryParameter.find(L"="));
			string_t value = queryParameter.substr(queryParameter.find(L"=") + 1, queryParameter.size() - 1);
			return value;
		}

		return L"";
	}

	//< Gets the relative url /images e.g >//
	static string_t getRelativeUri(http_request request) {
		string_t relativeUri = request.relative_uri().to_string();
		string_t relativeUriFormatted = relativeUri.substr(0, relativeUri.find(L"?"));
		return relativeUriFormatted;
	}

	void static replace_all(const std::wstring& oldStr, std::wstring& str, const std::wstring& newStr){
		size_t pos = 0;
		while ((pos = str.find(oldStr, pos)) != std::string::npos){
			str.replace(pos, oldStr.length(), newStr);
			pos += newStr.length();
		}
	}

	//< Gets the current working directory path >//
	static string_t getCurrentWorkingDirectory() {
		HMODULE hModule = GetModuleHandleW(NULL);
		WCHAR path[MAX_PATH];
		GetModuleFileNameW(hModule, path, MAX_PATH);
		//PathCchRemoveFileSpec(path, MAX_PATH);
		wstring exePath(path);
		wstring readPath;
		wstring imageName = L"ImageServer.exe";
		//exePath.replace("ImageServer.exe", "load.xml");
		//replace_all(exePath.begin(), exePath.end(), "ImageServer.exe", "load.xml");
		replace_all(imageName,exePath, readPath);
		return exePath;
	}

	static bool hasFile(string_t fileName) {
			struct _stat buffer;
			return (_wstat(fileName.c_str(), &buffer) == 0);
		}
	
};

#endif