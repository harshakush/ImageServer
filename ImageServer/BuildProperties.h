#ifndef BUILD_PROP_HEADER
#define BUILD_PROP_HEADER
#include <iostream>

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

private:
	string m_hostip;
	string m_hostEndpoint;
};

#endif