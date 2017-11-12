#include "webanalysis.h"

webAnalysis::webAnalysis(int tnumber):
	pagenumber(tnumber),
	hp(tnumber)
{
}

webAnalysis::~webAnalysis()
{
}

bool webAnalysis::extractInfo()
{
	return hp.parseAllHtml("buffer\\page");
}

bool webAnalysis::initDictionary()
{
	if (!wp.getDic("common.dic"))
		return false;
	if (!wp.getSpdic("sp.dic"))
		return false;
	return true;
}

bool webAnalysis::divideWords()
{

	return false;
}
