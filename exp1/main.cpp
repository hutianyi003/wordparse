#include <clocale>
#include <iostream>
#include "webanalysis.h"
#include "webdownload.h" 
#include "retrieve.h"


int main() {
	setlocale(LC_ALL, "chi");//set chinese language environment
	//start the project
	//webAnalysis wa(pagenumer, "buffer\\page",downhtml.url);
	//wa.extractInfo();
	//wa.initDictionary();
	//wa.divideWords();
	//wa.output("output\\result.csv");

    retrieve searchengine(2000, 40000);
    searchengine.init("word.csv");
    searchengine.exec("query.txt", "result.txt");
	return 0;
}