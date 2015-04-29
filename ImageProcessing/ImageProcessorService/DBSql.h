#ifndef DB_SQL
#define DB_SQL

#include "ServerUtils.h"
#include "sqlite3.h"
#include <memory>
using namespace std;


class DBSql {

public:
	~DBSql() {
		sqlite3_close(db);
	}
	static DBSql getInstance() {
		static DBSql instance;
		return instance;
	}

	 vector<string> getFileNames(void) {
		int rc;
		char *sql = "SELECT value from MyTable";
		char *zErrMsg = 0;
		char *data = "";
		rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
		if (rc != SQLITE_OK){
			//fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else{
			//fprintf(stdout, "Operation done successfully\n");
		}

		return fileNames;
	}

	static int callback(void *data, int argc, char **argv, char **azColName){
		int i;
		//	fprintf(stderr, "%s: ", (const char*)data);
		for (i = 0; i<argc; i++){
		//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
			string str(argv[i]);
			fileNames.push_back(str);
		}
	//	printf("\n");
		return 0;
	}

private:
	DBSql() {
		connect();
	}
	
	sqlite3 *db;
	static vector<string> fileNames;

	void connect() {
		int rc;
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

};
//typedef shared_ptr<DBSql> DBSqlPtr;

#endif