#include "ImageProcessor.h"


ImageProcessor::ImageProcessor(){}
void ImageProcessor::generateThumbNails(wstring aPath)
{
	generateFileListTxt(aPath);
	string line;
	ifstream myfile("C:\\Personal\\example123.txt");
	if (myfile.is_open())
	{
		while ( getline(myfile, line)) //make sure that these are images
		{
			
			cout << line << '\n';
			string lImgSrcLocation = "C:\\Personal\\"+line;
			string lImgDestiation = "C:\\Personal\\test\\"+line;

			string cmdToExecute = "gm convert -size 120x120 " + lImgSrcLocation + " -resize 120x120 +profile \"*\" " + lImgDestiation;
			const char *c_cmd = cmdToExecute.c_str();
			system(c_cmd);
		}
		myfile.close();
	}
}
void ImageProcessor::generateFileListTxt(wstring aPath)
{
	vector<wstring> lImageNames;// = getAllFiles(aPath);
	wofstream  myfile;

	myfile.open("C:\\Personal\\example123.txt");
	for (int i = 0; i < lImageNames.size(); i++) {
		myfile << lImageNames[i].c_str() << std::endl;
	}
	myfile.close();

}

long getFileSize(WIN32_FIND_DATA findData)
{
	long fDataFSize = (long)findData.nFileSizeLow;
	long fileSize = 0;

	if (fDataFSize < 0 && (long)findData.nFileSizeHigh > 0) {
		fileSize = fDataFSize + 4294967296 + ((long)findData.nFileSizeHigh * 4294967296);
	}
	else {
		if ((long)findData.nFileSizeHigh > 0) {
			fileSize = fDataFSize + ((long)findData.nFileSizeHigh * 4294967296);
		} else if (fDataFSize < 0) {
			fileSize = (fDataFSize + 4294967296);
		} else {
			fileSize = fDataFSize;
		}
	}
	return fileSize;
}

vector<CFile> ImageProcessor::getAllFiles(wstring aPath)
{
	vector<CFile> names;
	TCHAR search_path1[200];
	swprintf(search_path1, 200, L"%s\\*.*", aPath.c_str());
	WIN32_FIND_DATA fd;
	long filesize;
	HANDLE hFind = ::FindFirstFile(search_path1, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				//filesize = ::GetFileSize(hFind, NULL);
				CFile object(fd.cFileName, getFileSize(fd));
				names.push_back(object);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	return names;
}