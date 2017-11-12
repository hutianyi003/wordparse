#define _CRT_SECURE_NO_WARNINGS

#include "wordparse.h"
#include "mywds.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <set>


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

bool wordParse::exist(const std::string & word)
{
	if (sptable.find(word) != sptable.end())
		return true;
	if (hashtable.find(word) != hashtable.end())
		return true;
	return false;
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
