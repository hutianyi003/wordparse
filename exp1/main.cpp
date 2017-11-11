#include <iostream>
#include <fstream>
#include <tchar.h>
#include <clocale>
#include "webdownload.h"
#include "myds.h"

void output(ds::CharString& s) {
	int l = s.len();
	for (int i = 0; i < l; i++)
		std::cout << s[i];
	std::cout << std::endl;
}
int main() {
	//webDownloader down("url.csv", 1);
	//if (down.getHtml("buffer"))
		//std::cout << "ok" << std::endl;
	//std::ofstream output("testchi1.txt");
	/*
	std::locale china("chi");

	wds::CharString s;
	
	std::wifstream input("testchi1.txt");
	input.imbue(china);
	wchar_t c;
	std::wcout.imbue(china);
	while (input >> c) {
		std::wcout << c;
	}*/
	ds::Stack<ds::CharString> s;
	s.push(ds::CharString("123"));
	s.push(ds::CharString("456"));
	s.push(ds::CharString("789"));
	for (int i = 0; i < 3; i++) {
		output(s.top());
		s.pop();
	}
	return 0;
}