#ifndef SERVER_UTILS
#define SERVER_UTILS

#include<iostream>
#include <cpprest\asyncrt_utils.h>
#include <cpprest\http_headers.h>
#include <cpprest\http_msg.h>
#include<cpprest\rawptrstream.h> 
#include<cpprest\filestream.h>
#include <cpprest\asyncrt_utils.h>
#include<cpprest\producerconsumerstream.h>

using namespace std;
using namespace web::http;
using namespace concurrency::streams;
using namespace utility;



class ServerUtils
{
public:
	static void getRestDemo() {
		string storage = "Harsha";
	}

	static void return_failed() {
		string storage = "failed";
	}

	//this will return map, will be done when required.
	static string_t getQueryParameter(http_request request){
		string_t queryParameter = request.relative_uri().query();

		if (queryParameter.find(L"=")) {
			string_t name = queryParameter.substr(0, queryParameter.find(L"="));
			string_t value = queryParameter.substr(queryParameter.find(L"=") + 1, queryParameter.size() - 1);
			return value;
		}

		return L"";
	}
	

};

#endif