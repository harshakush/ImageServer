#include "DBSql.h"
#include "ServerMessages.hpp"
#include "DbQueries.hpp"
#include "ServerUtils.h"

DBSql::DBSql() {
	connect();
	createFileNamesTable();
}

//always make destructor virtual
DBSql::~DBSql() {
	sqlite3_close(db);
}

void DBSql::getAllFileMetaData(vector<CFile> & result) {
	
	sqlite3_stmt *statement;

	char *query = "SELECT FileName,FileSize from SqlLiteTable";

	if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK)
	{
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

		while (1)
		{
			res = sqlite3_step(statement);

			if (res == SQLITE_ROW)
			{
				int fileNameColumnPos = 0;
				int fileSizeColumnPos = 1;
				//read fileName 
				string sfName = (char*)sqlite3_column_text(statement, fileNameColumnPos);
				wstring fileName = ServerUtils::s2ws(sfName);
				//read fileSize & convert to long
				string sfSize = (char*)sqlite3_column_text(statement, fileSizeColumnPos);
				long fileSize = stol(sfSize);
				//create CFile object with fileName & fileSize
				CFile object(fileName,fileSize);
				result.push_back(object);
			
			}

			if (res == SQLITE_DONE || res == SQLITE_ERROR)
			{
				//cout << "done " << endl;
				break;
			}
		}
	}
	
}

void DBSql::saveMetaData(const CFile& fileData) {

	std::lock_guard<std::mutex> lock(m_dbMutex);
	int rc; char *error;
	
	string fileName = ServerUtils::ws2s(fileData.getFileName());
	char *sqlInsert = new char[fileName.length() + 50];

	string insertQueryStr = ServerUtils::ws2s(SqlLiteQueries::INSERT_METADATA);
	const char * insertQuery = insertQueryStr.c_str();
	sprintf(sqlInsert, insertQuery, fileName.c_str(), fileData.getFileSize(), "?", "?", "?");

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
	
		string tableCreateQuery = ServerUtils::ws2s(SqlLiteQueries::CREATE_SQLLITE_TABLE);
		const char * sqlCreateTable = tableCreateQuery.c_str();

		rc = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &error);
		if (rc)
		{
			//	cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
			sqlite3_free(error);
		}
		else
		{
			cout << "Created SqlLite table." << endl << endl;
		}
	}
