#ifndef DB_INTERFACE
#define DB_INTERFACE

#include <iostream>
#include <memory>

using namespace std;
//Create two subclasses
//DBJson :: public DBInterfacce
//DBPlainText :: public DBInterface
//DBSql :: public DBInterface

//For now implement just one function and make it work.
// Add row. Take it in incremental way.
class DBInterface {

	public:
		virtual ~DBInterface() {}
		virtual void addRow() = 0;
/*		virtual void updateRow() = 0;
		virtual void deleteRow() = 0;
		virtual void getAllRows() = 0;
		virtual void deleteAllRows() = 0;
		virtual void lock() = 0;
		virtual void unlock() = 0;*/
	private:	

};
typedef shared_ptr<DBInterface> DBInterfacePtr;

#endif