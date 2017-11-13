#include <clocale>
#include "webanalysis.h"


int main() {
	setlocale(LC_ALL, "chi");
	webAnalysis wa(100, "buffer\\page");
	wa.extractInfo();
	wa.initDictionary();
	wa.divideWords();
	wa.output("output\\result.csv");
	return 0;
}