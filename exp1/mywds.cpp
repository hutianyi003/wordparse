#include "mywds.h"
#include <cstring>
#include <tchar.h>
#include <wchar.h>

wds::CharString::CharString(int newsize) :sp(nullptr), lenth(newsize)
{
	if (newsize != 0)
		sp = new texttype[newsize];
}

wds::CharString::CharString(const texttype * s)
{
	lenth = std::wcslen(s);
	sp = new texttype[lenth];
	std::memcpy(sp, s, lenth * sizeof(texttype));
}

wds::CharString::CharString(const CharString & rhs) :lenth(rhs.len())
{
	sp = new texttype[lenth];
	std::memcpy(sp, rhs.getbase(), lenth * sizeof(texttype));
}

wds::CharString::~CharString()
{
	delete[] sp;
}

const int wds::CharString::len() const
{
	return lenth;
}

int wds::CharString::indexOf(const CharString & sub)
{
	int sublen = sub.len();
	if (sublen > lenth)
		return -1;
	for (int i = 0; i <= lenth - sublen; i++) {
		bool flag = true;
		for (int j = i; j < i + sublen; j++)
			if (sp[j] != sub.getbase()[j - i]) {
				flag = false;
				break;
			}
		if (flag == true)
			return i;
	}
	return -1;
}

wds::texttype * const wds::CharString::getbase() const
{
	return sp;
}

wds::CharString wds::CharString::substring(int pos, int sublen)const
{
	if (pos < 0 || pos >= lenth)
		return CharString();
	if (pos + sublen > lenth)
		sublen = lenth - pos;
	CharString temps(sublen);
	std::memcpy(temps.getbase(), sp + pos, sublen * sizeof(texttype));
	return temps;
}

void wds::CharString::concat(const CharString & rhs)
{
	texttype * temps = new texttype[lenth + rhs.len()];
	std::memcpy(temps, sp, lenth * sizeof(texttype));
	std::memcpy(temps + lenth, rhs.getbase(), rhs.len() * sizeof(texttype));
	lenth += rhs.len();
	delete[] sp;
	sp = temps;
}

wds::CharString & wds::CharString::operator=(const CharString & rhs)
{
	if (this == &rhs)
		return (*this);
	lenth = rhs.len();
	if (sp != nullptr)
		delete sp;
	sp = new texttype[lenth];
	memcpy(sp, rhs.getbase(), lenth * sizeof(texttype));
	return (*this);
}