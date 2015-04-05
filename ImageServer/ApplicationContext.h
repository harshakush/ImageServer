#ifndef BUILD_PROP_HEADER
#define BUILD_PROP_HEADER
#include <iostream>
#include "tinyxml2.h"
#include "ServerUtils.h"

using namespace std;
using namespace tinyxml2;

class ApplicationContext
{

private:
	ApplicationContext() {
		init();
	}

public:
	
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
			//eat it here.
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

private:
	wstring m_hostip;
	wstring m_hostEndpoint;
	wstring m_rootStoragePath;
	wstring m_rootDBPath;
	wstring m_port;
	
};

typedef shared_ptr<ApplicationContext> ApplicationContextPtr;

#endif