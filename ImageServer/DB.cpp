#include "DB.h"

DBInterfacePtr DB::m_dbInterface;
std::once_flag DB::load_flag;

void  DB::init() {
	if (DB::m_dbInterface == NULL) {
		//read the type of db from xml file & do new accordingly, as of now doing new of dbsql()
		m_dbInterface = DBInterfacePtr(new DBSql());
	}
}

DB::~DB() {
	//Do any further clean up.
}

//call_once is thread safe C++11.
DBInterfacePtr DB::getDbInterface() {
	std::call_once(load_flag, DB::init);
	return DB::m_dbInterface;
}