#include "CharString.h"

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

int ds::CharString::indexOf(const CharString & sub) const
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

int ds::CharString::find(const texttype & tch)
{
	for (int i = 0; i < lenth; i++)
		if (sp[i] == tch)
			return i;
	return -1;
}

ds::texttype * const ds::CharString::getbase() const
{
	return sp;
}

std::string ds::CharString::cpp_str() const
{
	return std::string(sp, lenth);
}

ds::CharString ds::CharString::substring(int pos, int sublen)const
{
	if (pos < 0 || pos >= lenth || sublen == 0)
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

void ds::CharString::concat(const texttype & rhs)
{
	texttype * temps = new texttype[lenth + sizeof(texttype)];
	std::memcpy(temps, sp, lenth * sizeof(texttype));
	temps[lenth] = rhs;
	lenth += sizeof(texttype);
	delete[] sp;
	sp = temps;
}

ds::CharString & ds::CharString::operator=(const CharString & rhs)
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

bool ds::CharString::operator==(const CharString & rhs) const
{
	if (lenth != rhs.len())
		return false;
	texttype *rhsbase = rhs.getbase();
	for (int i = 0; i < lenth; i++)
		if (sp[i] != rhsbase[i])
			return false;
	return true;
}