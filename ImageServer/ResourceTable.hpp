
#ifndef RESOURCE_TABLE_HEADER
#define RESOURCE_TABLE_HEADER

#include "RestInterface.h"
#include "ImagesResource.h"

using namespace std;

template<typename T> RestInterface* createInstance() { 
	return new T; 
}

typedef function<RestInterfacePtr()> FactoryType;
//typedef std::map<std::string, FactoryType> ResourceTableType;
//typedef std::map<std::string, FactoryType> ResourceTableType;
typedef std::map<std::string, RestInterface*(*)()> ResourceTableType;

class ResourceTable {
	ResourceTableType m_resourceTable;

public:
	ResourceTable() {
		m_resourceTable.insert(make_pair("http://localhost:6060/rest/images", &createInstance<ImagesResource>));
	}

	RestInterfacePtr getResource(string endpoint) {
		return RestInterfacePtr(m_resourceTable[endpoint]());		
	}

};

#endif