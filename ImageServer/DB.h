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
		//dbInterfacePtr = DBJsonPtr(new DBJson());

	}
	/*void useDBJson() {
	dbInterfacePtr = DBJsonPtr(new DBJson());
	}
	void useDBSql() {
	dbInterfacePtr = DBSqlPtr(new DBSql());
	}*/

	static DBInterfacePtr getDbInterface() {
		if (dbInterface == NULL) {
			//read the type of db from xml file & do new accordingly, as of now doing new of dbsql()
			dbInterface = DBSqlPtr(new DBSql());
		}
		return dbInterface;
	}
private:
	//DBInterfacePtr dbInterfacePtr;
	static DBInterfacePtr dbInterface;

};

#endif