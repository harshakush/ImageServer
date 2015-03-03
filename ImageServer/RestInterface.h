
/** 
* This defines the interface for all the rest interfaces
*
*/

#ifndef REST_INTERFACE_HEADER
#define REST_INTERFACE_HEADER
 
#include <memory>
#include "ServerRequest.h"
#include "ServerResponse.h"

using namespace std;


class RestInterface {
public:
	virtual ServerResponsePtr get(const ServerRequestPtr request) = 0; 
	virtual ServerResponsePtr post(const ServerRequestPtr request) = 0;
	virtual ServerResponsePtr put(const ServerRequestPtr request) = 0;
	virtual ServerResponsePtr del(const ServerRequestPtr request) = 0;
	virtual ServerResponsePtr dispatch(const ServerRequestPtr request) = 0;
private:

};
typedef shared_ptr<RestInterface> RestInterfacePtr;

#endif