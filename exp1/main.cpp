#include <iostream>
#include <fstream>
#include <tchar.h>
#include <clocale>
#include "webdownload.h"
#include "myds.h"
#include "mywds.h"

int main() {
	//webDownloader down("url.csv", 1);
	//if (down.getHtml("buffer"))
		//std::cout << "ok" << std::endl;
	//std::ofstream output("testchi1.txt");
	std::locale china("chi");

	wds::CharString s;
	
	std::wifstream input("testchi1.txt");
	input.imbue(china);
	wchar_t c;
	std::wcout.imbue(china);
	while (input >> c) {
		std::wcout << c;
	}
	return 0;
}