
#include<cpprest\details\basic_types.h>
using namespace utility;

namespace SqlLiteQueries {
	
	//create sample table with fileName
	const static wstring CREATE_TABLE = L"CREATE TABLE MyTable(id INTEGER PRIMARY KEY, value STRING); ";

	//create table with required metadata
	//fileName, filesize, dateaccessed, dateUploaded, fileformat (jpg,png etc )//
	const static wstring CREATE_SQLLITE_TABLE = L"CREATE TABLE SqlLiteTable( Id INTEGER PRIMARY KEY NOT NULL, FileName TEXT,FileSize INTEGER, DateAccessed INTEGER, DateUploaded INTEGER, FileType TEXT); ";
	
	const static wstring INSERT_METADATA = L"INSERT INTO SqlLiteTable VALUES(NULL,'%s','%s','%s','%s','%s');";
}