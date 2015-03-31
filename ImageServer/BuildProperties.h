#ifndef BUILD_PROP_HEADER
#define BUILD_PROP_HEADER
#include <iostream>
#include "tinyxml2.h"
#include "ServerUtils.h"

using namespace std;
using namespace tinyxml2;

class BuildProperties
{
public:
	BuildProperties() :m_hostip(L"localhost"), m_hostEndpoint(L"http://localhost:6060/rest") {	
		init();
	}

	wstring getHostIp(){
		return m_hostip;
	}

	wstring getHostEndPoint() {
		return m_hostEndpoint;
	}

	void init() {
		try {
			tinyxml2::XMLDocument doc;
			string exePath = ServerUtils::ws2s(ServerUtils::getCurrentWorkingDirectory());
			string xmlFilePath = exePath + "\\load.xml";
			doc.LoadFile(xmlFilePath.c_str());
			const char *val = doc.FirstChildElement("ImageServerConfig")->FirstChildElement("hostip")->GetText();
			string value(val);
			wstring ws;
			ws.assign(value.begin(), value.end());
			m_hostEndpoint = ws;
		}
		catch (exception &e) {
			//eat it here.
		}
	}

	wstring getHost() {		
		 return m_hostEndpoint;
	}

private:
	wstring m_hostip;
	wstring m_hostEndpoint;
	wstring m_port;
	
};

#endif