#pragma once
#include <string>
namespace ds {
	template<class datatype>
	class Stack {
	public:
		Stack<datatype>();
		Stack<datatype>(const Stack<datatype> &rhs);
		~Stack<datatype>();
		void pop();
		bool push(const datatype& rhs);
		datatype top();
		bool empty();
		int size();
	private:
		const static int EVERY_ADD_SIZE = 256;
		int stacksize, maxstacksize;
		datatype *base;
	};

	typedef char texttype;
	class CharString {
	public:
		CharString(int newsize = 0);
		CharString(const texttype* s);
		CharString(std::string& s);
		CharString(const CharString& rhs);
		CharString& operator = (const CharString &rhs);
		~CharString();

		inline const int len() const;
		inline texttype* const getbase()const;

		inline texttype& operator[] (int p) {
			return sp[p];
		}
		inline texttype operator[] (int p) const {
			if (p >= lenth)
				return 0;
			return sp[p];
		}
		int indexOf(const CharString& sub);
		int find(const texttype& tch);
		CharString substring(int pos,int sublen)const;

		void concat(const CharString& rhs);
		bool operator == (const CharString& rhs)const;
		//const CharString operator + (const CharString& rhs);
		//bool assign(const CharString& rhs);
	private:
		texttype *sp;
		int lenth;
	};
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
		inline int size()const;
	private:
		linkNode * head, *tail;
		int lenth;
	};


/*------------------------stack--------------------------------*/
	template<class datatype>
	inline Stack<datatype>::Stack() :stacksize(0), maxstacksize(EVERY_ADD_SIZE)
	{
		base = new datatype[maxstacksize];
		return;
	}
	template<class datatype>
	inline Stack<datatype>::Stack(const Stack<datatype>& rhs):
		stacksize(rhs.stacksize),
		maxstacksize(rhs.maxstacksize)
	{
		base = new[maxstacksize];
		for (int i = 0; i < stacksize; i++)
			*(base + i) = *(rhs.base + i);
		return;
	}
	template<class datatype>
	inline Stack<datatype>::~Stack()
	{
		delete[] base;
		return;
	}
	template<class datatype>
	inline void Stack<datatype>::pop()
	{
		if (stacksize == 0) return;
		stacksize--;
	}
	template<class datatype>
	inline bool Stack<datatype>::push(const datatype & rhs)
	{
		if (stacksize == maxstacksize) {
			maxstacksize += EVERY_ADD_SIZE;
			datatype *newbase = new datatype[maxstacksize];
			for (int i = 0; i < stacksize; i++)
				*(newbase + i) = *(base + i);
			delete[] base;
			base = newbase;
		}
		base[stacksize++] = rhs;
		return true;
	}
	template<class datatype>
	inline datatype Stack<datatype>::top()
	{
		if (!stacksize) {
			throw 0;
		}
		return base[stacksize-1];
	}
	template<class datatype>
	inline bool Stack<datatype>::empty()
	{
		return (stacksize == 0);
	}
	template<class datatype>
	inline int Stack<datatype>::size()
	{
		return stacksize;
	}
}
