#include "webdownload.h"
#include <string>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <urlmon.h>
#include <direct.h>
#pragma comment(lib,"urlmon.lib")

webDownloader::webDownloader(const std::string& tname, const int tn) :
	inputfilename(tname), urlnumber(tn)
{
}

webDownloader::~webDownloader()
{
}

bool webDownloader::getHtml(const std::string& Path)
{
	if (!getUrlFromCsv())
		return false;

	//check if the path existed or is created successfully
	if (_mkdir(Path.c_str()) != 0 && errno != EEXIST)
			return false;
	
	std::cout << "Start getting htmls from url.csv" << std::endl;
	for (int i = 0; i < urlnumber; i++) {
		std::string filepath(Path);
		filepath += ("\\page" + std::to_string(i) + ".html");
		std::wstring wfilepath;
		wfilepath.assign(filepath.begin(), filepath.end());
		HRESULT result = URLDownloadToFileW(0, url[i].c_str(), const_cast<LPWSTR>(wfilepath.c_str()), 0, NULL);
		if (result != S_OK)
			return false;
		if (i % 10 == 9) {
			std::cout << i + 1 << " has completed" << std::endl;
		}
	}
	return true;
}

bool webDownloader::getUrlFromCsv()
{
	std::ifstream input(inputfilename);
	if (!input) {
		return false;
	}
	std::string temp;
	std::wstring turl;
	getline(input, temp);//ignore the first line
	while (std::getline(input, temp)) {
		for (std::string::iterator i = temp.begin(); i != temp.end(); i++) {
			if ((*i) == '"') {
				turl.assign(i + 1, temp.end() - 1);
				break;
			}
		}
		url.push_back(turl);
	}
	if (url.size() == urlnumber)//check if success
		return true;
	else
		return false;
}
