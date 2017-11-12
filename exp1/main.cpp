#include <iostream>
#include <fstream>
#include <tchar.h>
#include <clocale>
#include "webdownload.h"
#include "myds.h"
#include "wordparse.h"
#include "htmlparse.h"

void output(ds::CharString& s) {
	int l = s.len();
	for (int i = 0; i < l; i++)
		std::cout << s[i];
	std::cout << std::endl;
}
int main() {
	setlocale(LC_ALL, "chi");
	//webDownloader down("url.csv", 1);
	//if (down.getHtml("buffer"))
		//std::cout << "ok" << std::endl;
	//std::ofstream output("testchi1.txt");
	/*
	std::wifstream input("testchi1.txt");
	input.imbue(china);
	wchar_t c;
	std::wcout.imbue(china);
	while (input >> c) {
		std::wcout << c;
	}
	
	std::ofstream output("outchi.csv");
	wchar_t head = '\xFE\xFF';
	wchar_t c = L'\xf2\xb4';
	char a = '\xf2', b = '\xb4';
	if (!output) {
		std::cout << "failed" << std::endl;
	}
	output << c;*/
	htmlParse hp(100);
	hp.parseAllHtml();
	return 0;
}