#pragma once
#include "htmlparse.h"
#include "wordparse.h"

class webAnalysis{
public:
	webAnalysis(int tnumber);
	~webAnalysis();
	bool extractInfo();
	bool initDictionary();
	bool divideWords();
private:
	htmlParse hp;
	wordParse wp;

	int pagenumber;
};