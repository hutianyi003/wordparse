#pragma once
#include "htmlparse.h"
#include "wordparse.h"

class webAnalysis{
public:
	webAnalysis(int tnumber, const std::string& pre);
	~webAnalysis();
	bool extractInfo();
	bool initDictionary();
	bool divideWords();

private:
	static const int MaxDivideLenth = 5;
	bool divideOnePage(int now);
	bool divide(ds::CharStringLink& store, const ds::CharString& context);
	htmlParse hp;
	wordParse wp;
	std::string webprefilename;
	ds::CharStringLink titlewords, contextwords;

	int pagenumber;
};