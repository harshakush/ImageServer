#include "image_operations.h"

ServerResponsePtr ImageOperations::generateThumbnail(const ServerRequestPtr request)
{
	//string cmd = "gm convert -size 120x120 " + aImgName + " -resize 120x120 +profile \"*\" testmanu.jpg";
//	const char *c_cmd = cmd.c_str();
//	system(c_cmd);
	ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
	response->setResponse("simple response.. Generating thumbnail of img in progress");

	return response;
}

ServerResponsePtr ImageOperations::resizeImage(const ServerRequestPtr request)
{
	ServerResponsePtr response = ServerResponsePtr(new ServerResponse());
	
	request->getJson();
	//extraction of img
	string lImgSrcLocation = "C:\\Users\\mmanu\\test_image_folder\\IMG_0909.JPG";
	string lImgDestiation = "C:\\Users\\mmanu\\test_image_folder\\testImage.JPG";

	string cmdToExecute = "gm convert -size 120x120 " + lImgSrcLocation + " -resize 120x120 +profile \"*\" " + lImgDestiation;
	const char *c_cmd = cmdToExecute.c_str();
	system(c_cmd);

	response->setResponse("simple response.. Resizing of img in progress");
	
	return response;

}