#pragma once

#include "CharString.h"

namespace ds {
    /*
    *������������ͻ��һ����ϣʵ��
    *����������κθ��ơ��ƶ�����
    *��ϣԪ��Ϊ�Զ�����ַ�������
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