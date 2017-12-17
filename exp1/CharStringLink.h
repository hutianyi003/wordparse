#pragma once
#include "CharString.h"

namespace ds {
	class linkNode {
	public:
		linkNode(const CharString &td, linkNode* tnext);
		CharString d;
		linkNode* next;
	};
	class CharStringLink {
	public:
		CharStringLink();
		~CharStringLink();

		bool add(const CharString &rhs,int place = -1);
		bool remove(int place);
		int search(const CharString& searchfor)const;
		CharString get(int place);

		inline int size()const {
			return lenth;
		}

	private:
		linkNode * head, *tail;
		int lenth;
	};
}