#ifndef DB_JSON
#define DB_JSON

#include "DBInterface.h"
#include <memory>
using namespace std;

//For now implement just one function and make it work.
// Add row. Take it in incremental way.
class DBJson : public DBInterface {

public:
	DBJson() {}
	virtual void addRow() {

	}
	
private:

};
typedef shared_ptr<DBJson> DBJsonPtr;

#endif