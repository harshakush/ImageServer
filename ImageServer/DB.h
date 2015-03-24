#ifndef DB_HEADER
#define DB_HEADER

#include <iostream>
#include "DBInterface.h"
#include "DBJson.h"
#include "DBSql.h"

using namespace std;

class DB {
public:
	DB() {
		dbInterfacePtr = DBJsonPtr(new DBJson());
	}
	void useDBJson() {
		dbInterfacePtr = DBJsonPtr(new DBJson());
	}
	void useDBSql() {
		dbInterfacePtr = DBSqlPtr(new DBSql());
 	}
	DBInterfacePtr getDBhandle() {
		return dbInterfacePtr;
	}
private:
	DBInterfacePtr dbInterfacePtr;
};

#endif