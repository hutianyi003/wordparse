#pragma once
#include <vector>
#include "htmlparse.h"
#include "wordparse.h"

class webAnalysis{
public:
	webAnalysis(int tnumber, const std::string& pre);
	~webAnalysis();
	bool extractInfo();
	bool initDictionary();
	bool divideWords();
	void output(const std::string &outputfilename);

private:
	static const int MaxDivideLenth = 5;
	bool divideOnePage(int now);
	bool divide(ds::CharStringLink& store, const ds::CharString& context);
	void outputWords(int page, std::ofstream& output);

	htmlParse hp;
	wordParse wp;
	std::string webprefilename;
	std::vector<ds::CharStringLink> titlewords, contextwords;

	int pagenumber;
};