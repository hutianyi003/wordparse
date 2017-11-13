#pragma once
#include <string>
#include <vector>
class webDownloader {
public:
	webDownloader(const std::string&,const int);
	~webDownloader();
	bool getHtml(const std::string&);
private:
	std::vector<std::wstring> url;
	std::string inputfilename;
	int urlnumber;
	bool getUrlFromCsv();
};