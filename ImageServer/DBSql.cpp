#include "DBSql.h"

DBSql::DBSql() {
	connect();
	createFileNamesTable();
}

//always make destructor virtual
DBSql::~DBSql() {
	sqlite3_close(db);
}

void DBSql::saveMetaData(const CFile& fileData) {

	std::lock_guard<std::mutex> lock(m_dbMutex);
	int rc; char *error;
	wstring fileName = fileData.getFileName();
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

void DBSql::addRow() {

}


void DBSql::connect() {
		std::lock_guard<std::mutex> lock(m_dbMutex);
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


void DBSql::createFileNamesTable() {
		std::lock_guard<std::mutex> lock(m_dbMutex);
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
