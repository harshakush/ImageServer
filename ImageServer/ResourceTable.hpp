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
#include "BuildProperties.h"
#include "DefaultResource.hpp"
using namespace std;

template<typename T> RestInterface* createInstance() { 
	return new T; 
}

typedef std::map<std::string, RestInterface*(*)()> ResourceTableType;
typedef std::map<std::string, RestInterface*(*)()>::iterator ResourceTableTypeIter;

class ResourceTable {
	
public:
	ResourceTable() {
		m_resourceTable.insert(make_pair("/images", &createInstance<ImagesResource>));
	}


	RestInterfacePtr getResource(string endpoint) {
		//string hosttt = m_properties.getHost();
		ResourceTableTypeIter resourceItertator;
		for (resourceItertator = m_resourceTable.begin(); resourceItertator != m_resourceTable.end(); resourceItertator++) {
				string resourceName = resourceItertator->first;
				if (endpoint.find(resourceName) != std::string::npos) {
					return RestInterfacePtr((resourceItertator->second)());
				}
		}
		
 		return RestInterfacePtr(new DefaultResource());
	}	

private:
	BuildProperties m_properties;
	ResourceTableType m_resourceTable;

};

#endif