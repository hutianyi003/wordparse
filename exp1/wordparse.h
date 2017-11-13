#pragma once
#include <string>
#include <unordered_set>
#include "myds.h"

class wordParse {
public:
	wordParse();
	~wordParse();
	bool getDic(const std::string& tfilename);
	bool getSpdic(const std::string& tfilename);
	bool exist(const std::string word);

	static void entityToGbk(ds::CharString& totrans);

private:
	static const int bufferlen = 40;
	wchar_t* utf8ToUnicode(const std::string utf8s);

	std::unordered_set<std::string, std::hash<std::string> > hashtable;
	std::unordered_set<std::string, std::hash<std::string> > sptable;
};
