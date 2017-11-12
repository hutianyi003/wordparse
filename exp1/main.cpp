#include <clocale>
#include "webdownload.h"
#include "myds.h"
#include "webanalysis.h"

int main() {
	setlocale(LC_ALL, "chi");
	webAnalysis wa(100);
	wa.extractInfo();
	wa.initDictionary();
	return 0;
}