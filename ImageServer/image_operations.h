#ifndef IMAGE_OPERATIONS_HEADER
#define IMAGE_OPERATIONS_HEADER

#include <iostream>
#include <string>
#include "ServerRequest.h"
#include "ServerResponse.h"
using namespace std;

class ImageOperations {
private:
	string m_ImgName = "";
public:

	//ImageOperations(string aImgName);
	ServerResponsePtr generateThumbnail(const ServerRequestPtr request);
	ServerResponsePtr resizeImage(const ServerRequestPtr request);

};

#endif