#ifndef DB_SQL
#define DB_SQL

#include "DBInterface.h"
#include <memory>
using namespace std;

//For now implement just one function and make it work.
// Add row. Take it in incremental way.
class DBSql : public DBInterface {

public:
	DBSql() {}
	virtual void addRow() {

	}
	/*		virtual void updateRow() = 0;
	virtual void deleteRow() = 0;
	virtual void getAllRows() = 0;
	virtual void deleteAllRows() = 0;
	virtual void lock() = 0;
	virtual void unlock() = 0;*/
private:

};
typedef shared_ptr<DBSql> DBSqlPtr;

#endif