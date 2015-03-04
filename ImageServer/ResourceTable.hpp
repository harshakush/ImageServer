
#ifndef RESOURCE_TABLE_HEADER
#define RESOURCE_TABLE_HEADER

#include "RestInterface.h"
#include "ImagesResource.h"
#include "BuildProperties.h"
using namespace std;

template<typename T> RestInterface* createInstance() { 
	return new T; 
}

typedef std::map<std::string, RestInterface*(*)()> ResourceTableType;


static const string IMGAGES_RESOURCE = "/images";

class ResourceTable {
	ResourceTableType m_resourceTable;
	BuildProperties properties;

public:
	ResourceTable() {
		m_resourceTable.insert(make_pair(IMGAGES_RESOURCE, &createInstance<ImagesResource>));
	}


	RestInterfacePtr getResource(string endpoint) {

		m_resourceTable[endpoint];

		if (m_resourceTable[endpoint] != NULL) {
			return RestInterfacePtr(m_resourceTable[endpoint]());
		}			
		else {
			ResourceTableType::iterator resourceItertator;
			for (resourceItertator = m_resourceTable.begin(); resourceItertator != m_resourceTable.end(); resourceItertator++){
				string resourceName = resourceItertator->first;
				if (endpoint.find(resourceName) != std::string::npos) {
					return RestInterfacePtr((resourceItertator->second)());
				}
			}
		}
	}

};

#endif