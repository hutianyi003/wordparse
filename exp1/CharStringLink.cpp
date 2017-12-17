#include "CharStringLink.h"

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

ds::CharString ds::CharStringLink::get(int place)
{
	if (place < 0 || place >= lenth)
		return CharString();
	linkNode *p = head;
	while (place-- > 0) {
		p = p->next;
	}
	return p->d;
}

ds::linkNode::linkNode(const CharString & td, linkNode * tnext):
	d(td), next(tnext)
{
}