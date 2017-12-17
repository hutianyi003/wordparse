#include <fstream>

#include "webanalysis.h"

webAnalysis::webAnalysis(int tnumber, 
	const std::string& pre,
	const std::vector<std::string>& turls) :
	pagenumber(tnumber),
	hp(tnumber),
	webprefilename(pre),
	titlewords(tnumber),
	contextwords(tnumber),
	urls(turls)
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

void webAnalysis::output(const std::string & outputfilename)
{
	std::ofstream out(outputfilename);
	std::ifstream input("resulttemplate.txt");
	if (!input)
		return;
	std::string buffer;
	std::getline(input, buffer);
	out << buffer << std::endl;//output the firstline

	for (int i = 0; i < pagenumber; i++) {
		out << i + 1 << ",\"" << urls[i] << "\",";
		//if not exist, output NA
		if (hp.title[i].len() == 0) {
			out << "NA,NA,NA,NA,NA,NA,NA,NA" << std::endl;
			continue;
		}
		//output all infomations
		out << '\"' << hp.bigtype[i].cpp_str() << '\"' << ',';
		out << '\"' << hp.smalltype[i].cpp_str() << '\"' << ',';
		out << '\"' << hp.title[i].cpp_str() << '\"' << ',';
		out << '\"' << hp.context[i].cpp_str() << '\"' << ',';
		out << '\"' << hp.author[i].cpp_str() << '\"' << ',';
		out << '\"' << hp.date[i].cpp_str() << '\"' << ',';
		out << '\"' << hp.posttype[i].cpp_str() << '\"' << ',' << '\"';
		//output words
		outputWords(i, out);
		out << '\"' << std::endl;
	}
}

bool webAnalysis::divideOnePage(int now)
{
	// trans html entities to gbks
	if (!hp.isgbk[now]) {
		wordParse::entityToGbk(hp.context[now]);
	}
	if (!divide(titlewords[now], hp.title[now]))
		return false;
	if (!divide(contextwords[now], hp.context[now]))
		return false;
	return true;
}

bool webAnalysis::divide(ds::CharStringLink & store, const ds::CharString & context)
{
	int len = context.len();
	for (int i = 0; i < len; i++) {
		// parse numbers
		if (isdigit(context[i])) {
			int addlen = 1;
			while (isdigit(context[i + addlen])) {
				addlen++;
			}
			store.add(context.substring(i, addlen));
			i += (addlen - 1);
		}
		// from max lenth to parse words
		for (int j = MaxDivideLenth; j > 0; j--) {
			if (i + j * 2 > len)
				continue;
			ds::CharString cut = context.substring(i, j * 2);
			if (wp.exist(cut.cpp_str()))
			{
				store.add(cut);
				i += (2 * j - 1);
			}
		}
	}
	return true;
}

//output parsed words
//ignore all repeated words
void webAnalysis::outputWords(int page,std::ofstream& output)
{
	std::unordered_set<std::string, std::hash<std::string>> has;
	int size = titlewords[page].size();
	for (int i = 0; i < size; i++) {
		std::string word(titlewords[page].get(i).cpp_str());
		if (has.find(word) == has.end()) {
			output << word << ' ';
			has.insert(word);
		}
	}
	size = contextwords[page].size();
	for (int i = 0; i < size; i++) {
		std::string word(contextwords[page].get(i).cpp_str());
		if (has.find(word) == has.end()) {
			output << word << ' ';
			has.insert(word);
		}
	}
}
