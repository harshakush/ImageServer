#ifndef SERVER_PARAMETER
#define SERVER_PARAMETER

#include <map>
#include<memory>
#include<list>
using namespace std;

class ServerParameter {

public:
	ServerParameter() {

	}
	string getName() {
		return m_name;
	}

	void setName(string name) {
		m_name = name;
	}

	string getValue() {
		return m_value;
	}

	void setValue(string value) {
		m_value = value;
	}
private:
	string m_name;
	string m_value;
};
typedef shared_ptr<ServerParameter> ServerParameterPtr;

class ServerParametersInterfacce {
public:
	ServerParametersInterfacce() {
	}

	//Important in this case
	virtual ~ServerParametersInterfacce() {

	}

	virtual list<ServerParameterPtr> getParameters() = 0;
	virtual void setParameters(list<ServerParameterPtr> parameters) = 0;
	// Point to be noted, do some research here.
	virtual void addParameter(ServerParameterPtr parameter) = 0;
	
};
typedef shared_ptr<ServerParametersInterfacce> ServerParametersInterfaccePtr;


class ServerParameters : public ServerParametersInterfacce {

	public: ServerParameters() {
			}
			virtual list<ServerParameterPtr> getParameters() {
				return m_paramaterList;
			}
			virtual void setParameters(list<ServerParameterPtr> parameters) {
				m_paramaterList = parameters;
			}

			virtual void addParemeter(ServerParameterPtr parameter) { 
				m_paramaterList.push_back(parameter);
			}

private: 
	list<ServerParameterPtr> m_paramaterList;
};
#endif