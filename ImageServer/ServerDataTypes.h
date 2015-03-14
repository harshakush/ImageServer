#ifndef SERVER_OPERATION_TYPES
#define SERVER_OPERATION_TYPES
#include <iostream>
#include <map>


using namespace std;
namespace ServerDataTypes {	

	enum class rest_methods {
		IGET = 0,
		IPOST = 1,
		IPUT = 2,
		IDELETE = 3
	};

	typedef rest_methods rest_operation;

	enum class ServerResponseType
	{
		JSON,
		STREAM,
		PLAIN_TEXT,
		INVALID
	};
		
	
}


#endif