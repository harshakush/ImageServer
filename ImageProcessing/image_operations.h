#include <iostream>
#include <string>
using namespace std;

class ImageOperations {
private:
	string m_ImgName = "";
public:
	
	//ImageOperations(string aImgName);
	void generateThumbnail(string aImgName);
	void resizeImage(string aImgName);

};