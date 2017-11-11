#pragma once
#include <string>
#include <tchar.h>

namespace wds {
	typedef wchar_t texttype;
	class CharString {
	public:
		CharString(int newsize = 0);
		CharString(const texttype* s);
		//CharString(std::string& s);
		CharString(const CharString& rhs);
		~CharString();

		inline const int len() const;
		int indexOf(const CharString& sub);
		inline texttype* const getbase()const;
		CharString substring(int pos, int sublen)const;
		void concat(const CharString& rhs);
		CharString& operator = (const CharString &rhs);
		//const CharString operator + (const CharString& rhs);
		//bool assign(const CharString& rhs);
	private:
		texttype *sp;
		int lenth;
	};
}