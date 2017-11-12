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
	const int bufferlen = 50;

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
		//check that if two words have the same hashkey 
		//no such case
		//if(hashtable.insert(str).second == false)
		//	std::cout << cbuf << std::endl;
		hashtable.insert(str);
		delete[] temp;
	}
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
