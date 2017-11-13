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

ds::CharStringLink::CharStringLink() :
	head(nullptr),
	tail(nullptr),
	lenth(0)
{
}

ds::CharStringLink::~CharStringLink()
{
	linkNode* p = head;
	while (p != tail) {
		head = p->next;
		delete p;
		p = head;
	}
	delete tail;
}

bool ds::CharStringLink::add(const CharString & rhs,int place)
{
	if (place < -1 || place >= lenth)
		return false;
	lenth++;
	if (head == nullptr) {
		head = new linkNode(rhs, nullptr);
		tail = head;
		return true;
	}
	if (place == -1 || place == lenth - 1) {
		tail->next = new linkNode(rhs, nullptr);
		tail = tail->next;
		return true;
	}
	linkNode *p = head;
	while (place--) {
		p = p->next;
	}
	linkNode *temp = new linkNode(rhs, p->next);
	p->next = temp;
	return true;
}

bool ds::CharStringLink::remove(int place)
{
	if (place < 0 || place >= lenth)
		return false;
	lenth--;
	if (place == 0) {
		linkNode *temp = head;
		head = head->next;
		delete temp;
		return true;
	}
	linkNode *p = head, *last = nullptr;
	while (place--) {
		last = p;
		p = p->next;
	}
	if (p == tail) {
		tail = last;
	}
	last->next = p->next;
	delete p;
	return true;
}

int ds::CharStringLink::search(const CharString & searchfor) const
{
	linkNode *p = head;
	int place = -1;
	for (int i = 0; i < lenth; i++) {
		if (p == nullptr)
			break;
		if (p->d == searchfor) {
			place = i;
			break;
		}
	}
	return place;
}

inline int ds::CharStringLink::size() const
{
	return lenth;
}

ds::linkNode::linkNode(const CharString & td, linkNode * tnext):
	d(td), next(tnext)
{
}
