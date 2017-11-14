#include <clocale>
#include "webanalysis.h"
#include "webdownload.h" 


int main() {
	//start the project
	webDownloader downhtml("input\\url.csv", 100);
	downhtml.getHtml("buffer");
	setlocale(LC_ALL, "chi");
	webAnalysis wa(100, "buffer\\page");
	wa.extractInfo();
	wa.initDictionary();
	wa.divideWords();
	wa.output("output\\result.csv");
	return 0;
}