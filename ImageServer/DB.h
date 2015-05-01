#ifndef DB_HEADER
#define DB_HEADER

#include <iostream>
#include "DBInterface.h"
#include "DBJson.h"
#include "DBSql.h"
#include <thread>
#include <mutex>

using namespace std;
using namespace utility;

class DB {

private:
	//if there is no defination use default
	DB()  = default;

	void static init();
	
public:	
	virtual ~DB();

	//call_once is thread safe C++11.
	static DBInterfacePtr getDbInterface();

private:	
	static DBInterfacePtr DB::m_dbInterface;
	static std::once_flag DB::load_flag;

};

#endif