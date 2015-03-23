#ifndef IMAGE_ACCOUNT_HEADER
#define IMAGE_ACCOUNT_HEADER


#include <iostream>
#include <memory>
using namespace std;

class ImageAccount {

public :
	
	void setAccountNumber(const wstring& number){
		m_accountNumber = number;
	}

	void setAccountName(const wstring& name){
		m_accountName = name;
	}

	wstring getAccountNumber(){
		return m_accountNumber;
	}

	wstring getAccountName(){
		return m_accountName;
	}


private: 
	wstring m_accountNumber;
	wstring m_accountName;
};

typedef shared_ptr<ImageAccount> ImageAccountPtr;

#endif