#ifndef BUILD_PROP_HEADER
#define BUILD_PROP_HEADER
#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

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

	 static wstring getHost() {

				tinyxml2::XMLDocument doc;
				doc.LoadFile("C:\\load.xml");
				const char *val = doc.FirstChildElement("ImageServerConfig")->FirstChildElement("hostip")->GetText();
				string value(val);
				wstring ws;
				ws.assign(value.begin(), value.end());
				return ws;

	}
private:
	string m_hostip;
	string m_hostEndpoint;
	
	
};

#endif