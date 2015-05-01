#ifndef DB_INTERFACE
#define DB_INTERFACE

#include "sqlite3.h"
#include <iostream>
#include <memory>
#include "CFile.hpp"

using namespace std;


class DBInterface {

public:
	virtual ~DBInterface() {}
	virtual void addRow() = 0;
	virtual void saveMetaData(const CFile &metaData) = 0;
	virtual void connect() = 0;

};

typedef shared_ptr<DBInterface> DBInterfacePtr;

#endif