#include "webdownload.h"
#include <thread>
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

void getonepage(const std::string from, const std::string to) 
{
	HRESULT result = URLDownloadToFile(0, from.c_str(), to.c_str(), 0, NULL);
}

bool webDownloader::getHtml(const std::string& Path)
{
	if (!getUrlFromCsv())
		return false;

	//check if the path existed or is created successfully
	if (_mkdir(Path.c_str()) != 0 && errno != EEXIST)
			return false;
	
	std::vector<std::thread> webthreads;
	for (int i = 0; i < urlnumber; i++) {
		//getonepage(url[i], (Path + "\\page" + std::to_string(i) + ".html"));
		webthreads.push_back(std::thread(getonepage, url[i], (Path+"\\page" + std::to_string(i) + ".html")));
	}
	for (int i = 0; i < urlnumber; i++)
		webthreads[i].join();
	return true;
}

bool webDownloader::getUrlFromCsv()
{
	std::ifstream input(inputfilename);
	if (!input) {
		return false;
	}
	std::string temp;
	std::string turl;
	getline(input, temp);//ignore the first line
	while (std::getline(input, temp)) {
		for (std::string::iterator i = temp.begin(); i != temp.end(); i++) {
			if ((*i) == '"') {
				turl.assign(i + 1, temp.end() - 1);
				break;
			}
		}
		url.push_back(turl);
		if (url.size() == urlnumber)
			break;
	}
	if (url.size() == urlnumber)//check if success
		return true;
	else
		return false;
}
