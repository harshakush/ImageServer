#ifndef DB_SQL
#define DB_SQL

#include "DBInterface.h"
#include "ServerUtils.h"

#include <memory>
using namespace std;

//For now implement just one function and make it work.
// Add row. Take it in incremental way.
class DBSql : public DBInterface {

public:
	DBSql() {
		connect();
		createFileNamesTable();
	}
	~DBSql() {
		sqlite3_close(db);
	}

	void saveMetaData(const MetaData &metaData) {
		int rc; char *error;
		string fileName = metaData.getFileName();
		char *sqlInsert = new char[fileName.length() + 50];
		sprintf(sqlInsert, "INSERT INTO MyTable VALUES(NULL, '%s');", fileName.c_str());

		//const char *sqlInsert = "INSERT INTO MyTable VALUES(NULL, 'A Value');";
		rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
		if (rc)
		{
			cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
			sqlite3_free(error);
		}
		else
		{
			cout << "Inserted a value into MyTable." << endl << endl;
		}
		free(sqlInsert);

	}
	virtual void addRow() {

	}


private:
	sqlite3 *db;

	void connect() {
		int rc;
		// read the db file name from xml file config ??
		string exePath = ServerUtils::ws2s(ServerUtils::getCurrentWorkingDirectory());
		string dbFilePath = exePath + "\\myTestDb.db";
		rc = sqlite3_open(dbFilePath.c_str(), &db);
		if (rc) {
			//need to use logger to log all the msgss
			//cout << "error opening connection" << endl;
			sqlite3_close(db);
		}
		else {
			//cout << "opened connection" << endl;
		}
	}


	void createFileNamesTable() {
		int rc;
		char * error;
		const char *sqlCreateTable = "CREATE TABLE MyTable (id INTEGER PRIMARY KEY, value STRING);";
		rc = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &error);
		if (rc)
		{
			//	cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
			sqlite3_free(error);
		}
		else
		{
			cout << "Created MyTable." << endl << endl;
		}
	}
};
typedef shared_ptr<DBSql> DBSqlPtr;

#endif