#include <iostream>
#include "webdownload.h"
#include "myds.h"

int main() {
//	webDownloader down("url.csv", 100);
//	if (down.getHtml("buffer"))
//		std::cout << "ok" << std::endl;
	ds::CharString s("Hello World");
	s.concat(ds::CharString(" HTY"));
	int flag = s.indexOf(ds::CharString("H"));
	std::cout << flag << std::endl;
	return 0;
}