#ifndef BUILD_PROP_HEADER
#define BUILD_PROP_HEADER
#include <iostream>

using namespace std;

class BuildProperties
{
public:
	BuildProperties() {
		m_hostip = "192.168.1.33";
	}

	string getHostIp() {
		return m_hostip;
	}
private:
	string m_hostip;
};

#endif