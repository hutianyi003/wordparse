#include <clocale>
#include "webanalysis.h"
#include "webdownload.h" 


int main() {
	//download html and get urlnumber
	int pagenumer = 2000;
	webDownloader downhtml("input\\url.csv", pagenumer);
	//downhtml.getHtml("buffer");

	setlocale(LC_ALL, "chi");//set chinese language environment
	//start the project
	webAnalysis wa(pagenumer, "buffer\\page",downhtml.url);
	wa.extractInfo();
	wa.initDictionary();
	wa.divideWords();
	wa.output("output\\result.csv");
	return 0;
}