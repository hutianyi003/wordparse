#include <clocale>
#include "webdownload.h"
#include "myds.h"
#include "webanalysis.h"

int main() {
	setlocale(LC_ALL, "chi");
	webAnalysis wa(100, "buffer\\page");
	wa.extractInfo();
	wa.initDictionary();
	wa.divideWords();
	return 0;
}