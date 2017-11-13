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

wchar_t transOneCharacter(const ds::CharString& oneword, int& place) {
	int sum = 0;
	if (oneword[place+1] == 'n') {
		place += 5;
		return wchar_t(L' ');
	}
	place += 2;
	while (isdigit(oneword[place])) {
		sum = sum * 10 + oneword[place] - '0';
		place++;
	}
	return wchar_t((sum & 0x0000FFFF));
}

void wordParse::entityToGbk(ds::CharString & totrans)
{
	int len = totrans.len();
	std::vector<wchar_t> wcharunicode;
	for (int i = 0; i < len; i++) {
		if (totrans[i] == '&') {
			wcharunicode.push_back(transOneCharacter(totrans, i));
		}
		else {
			wcharunicode.push_back(0x00FF & totrans[i]);
		}
	}

	int wsize = wcharunicode.size();
	wchar_t *wc = new wchar_t[wsize + 1];
	for (int i = 0; i < wsize; i++) {
		wc[i] = wcharunicode[i];
	}
	wc[wsize] = 0;

	int csize = 2 * wsize;
	char * chargbk = new char[csize + 1];
	memset(chargbk, 0, csize + 1);
	WideCharToMultiByte(CP_ACP, NULL, wc, wcslen(wc), chargbk, csize, NULL, NULL);
	chargbk[csize] = '\0';

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
