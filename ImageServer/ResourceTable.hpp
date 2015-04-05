/**********************************************************************************************
* This class stores all the available resource files. The templatized function helps
* in creating a new instance of the resource class. This acts more like a factory class
* Ideally this class should use trie data structure to store the url and functor mapping.
* By doing so we
***********************************************************************************************/
#ifndef RESOURCE_TABLE_HEADER
#define RESOURCE_TABLE_HEADER

#include "RestInterface.h"
#include "ImagesResource.h"
#include "ImageAccountsResource.hpp"
#include "ApplicationContext.h"
#include "DefaultResource.hpp"
#include <thread>
#include <mutex>
using namespace std;
using namespace utility;

template<typename T> RestInterface* createInstance() {
	return new T();
}

typedef std::map<wstring, RestInterface*(*)()> ResourceTableType;
typedef std::map<wstring, RestInterface*(*)()>::iterator ResourceTableTypeIter;

class ResourceTable {

public:

	//<The map is url to functor						  >//
	//<The method on execution always returns a new object>//
	ResourceTable() {			
	}

	//<release the map, otherwise these will be hanging>//
	~ResourceTable() {
		m_resourceTable.erase(m_resourceTable.begin(),m_resourceTable.end());
	}


	RestInterfacePtr getResource(wstring endpoint) {
		// Laxy initialization of the resources.
		// Till the first request reaches. 
		// This also thread safe initialization.

		std::call_once(load_flag,&ResourceTable::init,this);
		ResourceTableTypeIter iterResource = m_resourceTable.find(endpoint);
		RestInterface* restResource;

		if (iterResource == m_resourceTable.end()){
			restResource = new DefaultResource();
		}
		else {
			restResource = iterResource->second();
		}
		return RestInterfacePtr(restResource);
	}


private:

	void init() {
		m_resourceTable.insert(make_pair(L"/images", &createInstance<ImagesResource>));
		m_resourceTable.insert(make_pair(L"/accounts", &createInstance<ImageAccountsResource>));
	}

	std::once_flag load_flag;
	ResourceTableType m_resourceTable;
};

#endif
