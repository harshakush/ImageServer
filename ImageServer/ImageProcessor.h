#include <iostream>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <fstream>
#include <string>
#include "CFile.hpp"
using namespace std;


class ImageProcessor
{
private:

public:
	ImageProcessor();
	void generateThumbNails(wstring aPath);
	vector<CFile>  getAllFiles(wstring aPath);
	void generateFileListTxt(wstring aPath);
};