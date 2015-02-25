#include "image_operations.h"



void ImageOperations::generateThumbnail(string aImgName)
{
	cout << "Generating thumbnail " << aImgName.c_str()<<endl;
	
	string cmd = "gm convert -size 120x120 " + aImgName + " -resize 120x120 +profile \"*\" testmanu.jpg";
	const char *c_cmd = cmd.c_str();
	
	//system("gm convert -size 120x120 IMG_0909.JPG -resize 120x120 +profile \"*\" testmanu.jpg");
	system(c_cmd);
}

void ImageOperations::resizeImage(string aImgName)
{
	cout << "Resizing image" << aImgName.c_str()<< endl;

}