#include "webanalysis.h"
#include <iostream>

webAnalysis::webAnalysis(int tnumber, const std::string& pre) :
	pagenumber(tnumber),
	hp(tnumber),
	webprefilename(pre)
{
}

webAnalysis::~webAnalysis()
{
}

bool webAnalysis::extractInfo()
{
	return hp.parseAllHtml(webprefilename);
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
	for (int i = 0; i < pagenumber; i++) {
		if (!divideOnePage(i))
			return false;
	}
	return true;
}

bool webAnalysis::divideOnePage(int now)
{
	if (!hp.isgbk[now]) {
		return true;
	}
	if (!divide(titlewords, hp.title[now]))
		return false;
	if (!divide(contextwords, hp.context[now]))
		return false;
	return true;
}

bool webAnalysis::divide(ds::CharStringLink & store, const ds::CharString & context)
{
	int len = context.len();
	for (int i = 0; i < len; i++) {
		for (int j = MaxDivideLenth; j > 0; j--) {
			if (i + j * 2 > len)
				continue;
			ds::CharString cut = context.substring(i, j * 2);
			if (wp.exist(cut.cpp_str()))
			{
				store.add(cut);
				//std::cout << cut.cpp_str() << ' ';
				i += (2 * j - 1);
			}
		}
	}
	//std::cout << std::endl;
	return true;
}
