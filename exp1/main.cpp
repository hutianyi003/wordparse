#include <iostream>
#include <fstream>
#include <tchar.h>
#include "webdownload.h"
#include "myds.h"

int main() {
	//webDownloader down("url.csv", 1);
	//if (down.getHtml("buffer"))
		//std::cout << "ok" << std::endl;
	std::wofstream output("testchi1.txt",std::ios_base::binary);
	char32_t c = U'\x6253';
	output << c;
	return 0;
}