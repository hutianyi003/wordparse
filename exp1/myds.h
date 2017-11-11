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
		~CharString();

		inline const int len() const;
		int indexOf(const CharString& sub);
		inline texttype* const getbase()const;
		CharString substring(int pos,int sublen)const;
		void concat(const CharString& rhs);
		//const CharString operator + (const CharString& rhs);
		//bool assign(const CharString& rhs);
	private:
		texttype *sp;
		int lenth;
	};
	/*
	class CharStringLink {
	public:
		CharStringLink();
		CharStringLink(const CharStringLink &rhs);
		~CharStringLink();

		bool add(const CharString &rhs, const int place = -1);
		bool remove(const int place);
		int search(const CharString& searchfor);
	private:

	};*/
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
		std::memcpy(base, rhs.base, stacksize*sizeof(datatype));
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
			std::memcpy(newbase, base, stacksize * sizeof(datatype));
			delete[] base;
			base = newbase;
		}
		base[stacksize++] = rhs;
		return true;
	}
	template<class datatype>
	inline datatype Stack<datatype>::top()
	{
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
