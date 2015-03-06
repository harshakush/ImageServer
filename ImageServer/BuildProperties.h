#ifndef BUILD_PROP_HEADER
#define BUILD_PROP_HEADER
#include <iostream>
#include "tinyxml.h"

using namespace std;

class BuildProperties
{
public:
	BuildProperties() {
		m_hostip = "localhost";
		m_hostEndpoint = "http://localhost:6060/rest";
				
	}

	string getHostIp() {
		return m_hostip;
	}

	string getHostEndPoint() {
		return m_hostEndpoint;
	}

	 string getHost() {

		 try {
			 TiXmlDocument m_doc("C:\\load.xml");
			 m_doc.LoadFile();
			 TiXmlElement* root = m_doc.FirstChildElement("ImageServerConfig");

			 TiXmlElement* host = root->FirstChildElement("hostip");
			 return host->GetText();
		 }
		 catch (exception e) {
			 return "";
		 }
		
	}
private:
	string m_hostip;
	string m_hostEndpoint;
	
	
};

#endif