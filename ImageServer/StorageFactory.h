
/**
* Make it thread safe. And read the configutaion to some class from xml.
* 
*/

#ifndef STORAGE_FACTORY_HEADER
#define STORAGE_FACTORY_HEADER

#include<iostream>
#include "StorageInterface.h"
#include "FileSystemsStorage.h"

using namespace std;

class StorageFactory{

private:
	StorageFactory() {
	}
public:
	//Todo : How is this thread safe in C++11.
	//read about it.
	static StorageInterfacePtr getStorage() {	
		static StorageInterfacePtr m_storageInterface = StorageInterfacePtr(new FileSystemsStorage());		
		return m_storageInterface;
	}
};

#endif