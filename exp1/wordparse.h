#pragma once

#include <string>
#include <unordered_set>

#include "CharStringLink.h"

class wordParse {
public:
	wordParse();
	~wordParse();
	bool getDic(const std::string& tfilename);//get standard dictionary
	bool getSpdic(const std::string& tfilename);//get special dictionary
	bool exist(const std::string word);//check if word exists

	static void entityToGbk(ds::CharString& totrans);//trans html eneities to gbk

private:
	static const int bufferlen = 40;
	wchar_t* utf8ToGbk(const std::string utf8s);

	std::unordered_set<std::string, std::hash<std::string> > hashtable;
	std::unordered_set<std::string, std::hash<std::string> > sptable;
};
