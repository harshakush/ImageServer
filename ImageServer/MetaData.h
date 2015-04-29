#ifndef METADATA_H
#define METADATA_H

#include <iostream>
#include <memory>
using namespace std;

//do we need to make metadata an abstract class
// and then create classes like, imageMetaData etc ????
// now I created MetaData class just to hold the filename

class MetaData {

public:
	MetaData() {}
	~MetaData() {}
	
	string getFileName() const {
		return fileName;
	}
	string getFileSize() const {
		return fileSize;
	}
	void setFileName(string aFileName) {
		fileName = aFileName;
	}
	void setFileSize(string aFileSize) {
		fileSize = aFileSize;
	}
	
private:
	string fileName;
	string fileSize;
	//string fileowner;
};
typedef shared_ptr<MetaData> MetaDataPtr;


#endif