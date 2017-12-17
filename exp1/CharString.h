#pragma once
#include <string>

namespace ds {
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
		std::string cpp_str() const;

		//inline fuction must write in .h files
		inline texttype& operator[] (int p) {
			return sp[p];
		}
		inline texttype operator[] (int p) const {
			if (p >= lenth)
				return 0;
			return sp[p];
		}
		int indexOf(const CharString& sub)const;
		int find(const texttype& tch);
		CharString substring(int pos,int sublen)const;

		void concat(const CharString& rhs);
		void concat(const texttype& rhs);
		bool operator == (const CharString& rhs)const;
	private:
		texttype *sp;
		int lenth;
	};

}
