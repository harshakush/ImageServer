#ifndef DB_SQL
#define DB_SQL

#include "DBInterface.h"
#include "ServerUtils.h"
#include <memory>
#include <thread>
#include <mutex>

using namespace std;


class DBSql : public DBInterface {

public:
	DBSql();
	
	//always make destructor virtual
	virtual ~DBSql();

	void saveMetaData(const CFile& fileData);

	void addRow();

private: 
	void connect();

	void createFileNamesTable();

private:
	sqlite3 *db;
	std::mutex m_dbMutex;
	
};
typedef shared_ptr<DBSql> DBSqlPtr;

#endif