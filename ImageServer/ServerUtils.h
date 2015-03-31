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
#include <cvt/wstring>
#include <codecvt>

#define GetCurrentDir _getcwd


using namespace std;
using namespace web::http;
using namespace concurrency::streams;
using namespace utility;

class ServerUtils
{
public:
	// <this will return map, will be done when required.>//
	static wstring getQueryParameter(http_request request){
		wstring queryParameter = request.relative_uri().query();

		if (queryParameter.find(L"=")) {
			wstring name = queryParameter.substr(0, queryParameter.find(L"="));
			wstring value = queryParameter.substr(queryParameter.find(L"=") + 1, queryParameter.size() - 1);
			return value;
		}

		return L"";
	}

	//< Gets the relative url /images e.g >//
	static wstring getRelativeUri(http_request request) {
		wstring relativeUri = request.relative_uri().to_string();
		wstring relativeUriFormatted = relativeUri.substr(0, relativeUri.find(L"?"));
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
	static wstring getCurrentWorkingDirectory() {
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

	static bool hasFile(wstring fileName) {
			struct _stat buffer;
			return (_wstat(fileName.c_str(), &buffer) == 0);
		}
	static wstring s2ws(const std::string& str)
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	static string ws2s(const std::wstring& wstr)
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}
};

#endif