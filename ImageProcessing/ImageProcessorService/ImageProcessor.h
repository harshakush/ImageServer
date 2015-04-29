#include <iostream>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <fstream>
#include <string>
using namespace std;


class ImageProcessor
{
private:

public:
	ImageProcessor();
	void generateThumbNails(wstring aPath);
	vector<wstring>  get_all_imagenames_from_dir(wstring aPath);
	void generateFileListTxt(wstring aPath);
	void generatePreviews();
};