#ifndef BUILD_PROP_HEADER
#define BUILD_PROP_HEADER
#include <iostream>
#include "tinyxml2.h"
#include "ServerUtils.h"
#include "UnableToReadConfig.h"
#include "ResourceTable.hpp"


using namespace std;
using namespace tinyxml2;
//using namespace RessourceTypes;

class ApplicationContext
{

private:
	ApplicationContext() {
		init();
	}

	ApplicationContext(const ApplicationContext&rhs) {
		//no copy.
	}
	void operator=(ApplicationContext &rhs) {
		//no assignment, just private
	}


public:
	
	~ApplicationContext() {
		//any clean up needed.
	}

	static ApplicationContext getInstance() {
		static ApplicationContext instance;
		return instance;
	}

	wstring getHostIp(){
		return m_hostip;
	}

	wstring getHostEndPoint() {
		return m_hostEndpoint;
	}

	void init() {
		try {
			// First load the config file
			tinyxml2::XMLDocument doc;			
			string exePath = ServerUtils::ws2s(ServerUtils::getCurrentWorkingDirectory());
			string xmlFilePath = exePath + "\\load.xml";
			doc.LoadFile(xmlFilePath.c_str());

			// Read the attributes
			const char *val_hostIp = doc.FirstChildElement("ImageServerConfig")->FirstChildElement("hostip")->GetText();
			string value_hi(val_hostIp);
			m_hostEndpoint.assign(value_hi.begin(), value_hi.end());

			const char *val_file_system_root = doc.FirstChildElement("ImageServerConfig")->FirstChildElement("FileSystemRoot")->GetText();
			string value_hs(val_file_system_root);
			m_rootStoragePath.assign(value_hs.begin(), value_hs.end());

			const char *val_db_root = doc.FirstChildElement("ImageServerConfig")->FirstChildElement("DBRoot")->GetText();
			string value_hdb(val_file_system_root);
			m_rootDBPath.assign(value_hdb.begin(), value_hdb.end());

		}
		catch (exception &e) {
			UnableToReadConfigException configException;
			throw configException;
		}
	}

	wstring getHost() {		
		 return m_hostEndpoint;
	}

	wstring getRootStoragePath() {
		return m_rootStoragePath;
	}

	wstring getRootDBPath() {
		return m_rootDBPath;
	}

	/*ResourceTable getResourceTable() {
		return m_resourceTable;
	}
	*/
private:
	wstring m_hostip;
	wstring m_hostEndpoint;
	wstring m_rootStoragePath;
	wstring m_rootDBPath;
	wstring m_port;
	//ResourceTable m_resourceTable;
	
};

typedef shared_ptr<ApplicationContext> ApplicationContextPtr;

#endif