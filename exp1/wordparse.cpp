#define _CRT_SECURE_NO_WARNINGS

#include "wordparse.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <Windows.h>


wordParse::wordParse()
{
}

wordParse::~wordParse()
{
}

bool wordParse::getDic(const std::string & tfilename)
{

	std::ifstream input(tfilename);
	if(!input)
		return false;
	std::string buffer;
	char cbuf[bufferlen];
	getline(input, buffer);
	while (getline(input, buffer)) {
		wchar_t *temp = utf8ToUnicode(buffer);
		std::wcstombs(cbuf, temp, bufferlen);
		cbuf[wcslen(temp) * 2] = '\0';
		std::string str(cbuf);
		hashtable.insert(str);
		delete[] temp;
	}
	return true;
}

bool wordParse::getSpdic(const std::string & tfilename)
{

	std::ifstream input(tfilename);
	if(!input)
		return false;
	std::string buffer;
	char cbuf[bufferlen];
	getline(input, buffer);
	while (getline(input, buffer)) {
		wchar_t *temp = utf8ToUnicode(buffer);
		std::wcstombs(cbuf, temp, bufferlen);
		cbuf[wcslen(temp) * 2] = '\0';
		std::string str(cbuf);
		sptable.insert(str);
		delete[] temp;
	}
	return true;
}

bool wordParse::exist(const std::string word)
{
	if (sptable.find(word) != sptable.end())
		return true;
	if (hashtable.find(word) != hashtable.end())
		return true;
	return false;
}

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

void wordParse::entityToGbk(ds::CharString & totrans)
{
	ds::CharString unicodestring;
	int len = totrans.len();
	for (int i = 0; i < len; i++) {
		if (totrans[i] == '&') {
			transOneCharacter(unicodestring, totrans.substring(i, 8));
			i = i + 7;
		}
		else {
			unicodestring.concat(0);
			unicodestring.concat(totrans[i]);
		}
	}

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
	totrans = ds::CharString(chargbk);
	delete[] wc;
	delete[] chargbk;
	return;
}

wchar_t * wordParse::utf8ToUnicode(const std::string utf8s)
{
	char const *utf8string = utf8s.c_str();
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8string, -1, NULL, 0);
	if (len == 0)
		return L"";
	wchar_t * buffer = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, utf8string, -1, buffer, len);
	return buffer;
}
