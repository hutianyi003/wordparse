#pragma once

#include "CharString.h"

namespace ds {
    /*
    *基于链表解决冲突的一个哈希实现
    *不允许进行任何复制、移动操作
    *哈希元素为自定义的字符串类型
    */
    class hashtable {
        typedef ds::CharString elemtype;
        typedef int storetype;
    public:
        hashtable(int tn = 0);
        ~hashtable();
        hashtable(const hashtable&) = delete;
        hashtable& operator= (const hashtable&) = delete;
        hashtable(hashtable&&) = delete;
        hashtable& operator= (hashtable&&) = delete;

        bool insert(const elemtype&);
        storetype search(const elemtype&);
        inline int size();
    private:
        int max_hash_size;
        int now_size;
    };
}