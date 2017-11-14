#include <clocale>
#include "webanalysis.h"
#include "webdownload.h"


int main() {
	webDownloader downhtml("input\\url.csv", 1);
	downhtml.getHtml("buffer");

	setlocale(LC_ALL, "chi");
	//start the project
	//webAnalysis wa(100, "buffer\\page");
	//wa.extractInfo();
	//wa.initDictionary();
	//wa.divideWords();
	//wa.output("output\\result.csv");
	return 0;
}