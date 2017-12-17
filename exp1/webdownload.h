#pragma once
#include <string>
#include <vector>

class webDownloader {
public:
	webDownloader(const std::string&,int& number);
	~webDownloader();
	bool getHtml(const std::string&);
	std::vector<std::string> url;

private:
	std::string inputfilename;
	int& urlnumber;
	bool getUrlFromCsv();
};