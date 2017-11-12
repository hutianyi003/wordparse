#pragma once
#include <string>
#include <unordered_set>

class wordParse {
public:
	wordParse();
	~wordParse();
	bool getDic(const std::string& tfilename);

private:
	wchar_t* utf8ToUnicode(const std::string utf8s);
	std::unordered_set<std::string, std::hash<std::string> > hashtable;
};
