#include "myds.h"
#include <cstring>

ds::CharString::CharString(int newsize) :sp(nullptr), lenth(newsize)
{
	if (newsize != 0)
		sp = new texttype[newsize];
}

ds::CharString::CharString(const texttype * s)
{
	lenth = std::strlen(s);
	sp = new texttype[lenth];
	std::memcpy(sp, s, lenth * sizeof(texttype));
}

ds::CharString::CharString(std::string & s)
{
	new (this)CharString(s.c_str());
}

ds::CharString::CharString(const CharString & rhs) :lenth(rhs.len())
{
	sp = new texttype[lenth];
	std::memcpy(sp, rhs.getbase(), lenth * sizeof(texttype));
}

ds::CharString::~CharString()
{
	delete[] sp;
}

const int ds::CharString::len() const
{
	return lenth;
}

int ds::CharString::indexOf(const CharString & sub)
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

ds::texttype * const ds::CharString::getbase() const
{
	return sp;
}

ds::CharString ds::CharString::substring(int pos, int sublen)const
{
	if (pos < 0 || pos >= lenth)
		return CharString();
	if (pos + sublen > lenth)
		sublen = lenth - pos;
	CharString temps(sublen);
	std::memcpy(temps.getbase(), sp + pos, sublen * sizeof(texttype));
	return temps;
}

void ds::CharString::concat(const CharString & rhs)
{
	texttype * temps = new texttype[lenth + rhs.len()];
	std::memcpy(temps, sp, lenth * sizeof(texttype));
	std::memcpy(temps + lenth, rhs.getbase(), rhs.len() * sizeof(texttype));
	lenth += rhs.len();
	delete[] sp;
	sp = temps;
}
