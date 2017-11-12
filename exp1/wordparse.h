#pragma once
#include <string>
#include <unordered_set>

class wordParse {
public:
	wordParse();
	~wordParse();
	bool getDic(const std::string& tfilename);
	bool getSpdic(const std::string& tfilename);
	inline bool exist(const std::string& word);

private:
	static const int bufferlen = 30;
	wchar_t* utf8ToUnicode(const std::string utf8s);
	std::unordered_set<std::string, std::hash<std::string> > hashtable;

	std::unordered_set<std::string, std::hash<std::string> > sptable;
};