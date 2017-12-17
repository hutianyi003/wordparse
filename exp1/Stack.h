#pragma once
namespace ds {
    template<class datatype>
    class Stack {
    public:
        Stack<datatype>();
        Stack<datatype>(const Stack<datatype> &rhs);
        ~Stack<datatype>();
        void operator=(const Stack& rhs) = delete;
        void pop();
        bool push(const datatype& rhs);
        datatype top();
        bool empty();
        int size();
    private:
        const static int EVERY_ADD_SIZE = 256;//every time add memory size
        int stacksize, maxstacksize;
        datatype *base;
    };

	//templates must write in .h files
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
