#define _CRT_SECURE_NO_WARNINGS

#include <clocale>
#include <Windows.h>
#include "webdownload.h"
#include "myds.h"
#include "webanalysis.h"

#include <fstream>
#include <string>

void transOneCharacter(ds::CharString &ans, const ds::CharString& oneword) {
	int sum = 0;
	for (int i = 2; i <= 6; i++) {
		sum = sum * 10 + oneword[i] - '0';
	}
	char unicode[3];
	unicode[0] = static_cast<char>((sum >> 8) & 0xFF);
	unicode[1] = static_cast<char>(sum & 0xFF);
	unicode[2] = '\0';
	ans.concat(unicode[0]);
	ans.concat(unicode[1]);
	return;
}
void output(const ds::CharString &out) {
	int len = out.len();
	for (int i = 0; i < len; i++) {
		std::putchar(out[i]);
	}
}
int main() {
	setlocale(LC_ALL, "chi");
	//webAnalysis wa(100, "buffer\\page");
	//wa.extractInfo();
	//wa.initDictionary();
	//wa.divideWords();
	std::ifstream input("debugbuffer\\page0.html");
	freopen("testchi.txt", "w", stdout);
	if (!input) {
		return 1;
	}
	std::string buffer;
	std::getline(input, buffer);
	ds::CharString s(buffer);
	ds::CharString unicodestring;
	//char *temps = "\xFF\xFE";
	//unicodestring.concat(temps);
	int len = s.len();
	for (int i = 0; i < len; i++) {
		if (s[i] == '&') {
			transOneCharacter(unicodestring, s.substring(i, 8));
			i = i + 7;
		}
		else {
			unicodestring.concat(0);
			unicodestring.concat(s[i]);
		}
	}
	output(unicodestring);
	int csize = unicodestring.len();
	int wsize = csize / 2 + 1;
	wchar_t *wc = new wchar_t[wsize];
	for (int i = 0; i < csize; i += 2) {
		wchar_t first8size = unicodestring[i];
		wchar_t last8size = unicodestring[i+1];
		wchar_t onewchar = (first8size << 8) + (0x00FF & last8size);
		wc[i / 2] = onewchar;
	}
	wc[wsize - 1] = 0;

	char * chargbk = new char[csize+1];
	WideCharToMultiByte(CP_ACP, NULL, wc, wcslen(wc), chargbk, csize, NULL, NULL);
	chargbk[csize] = 0;
	std::string view(unicodestring.cpp_str());
	delete[] wc;
	delete[] chargbk;
	return 0;
}