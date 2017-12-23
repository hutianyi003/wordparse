#pragma once

#include <string>

#include "CharString.h"
#include "filelist.h"

namespace ds {
    /*
    ������������ͻ��һ����ϣʵ��
    ��ϣԪ��Ϊ�Զ�����ַ�������
    */
    class hashtable {
    public:

        typedef ds::CharString elemtype;

        class node {
        public:
            int wordid;
            CharString word;
            filelist* file;
            node* next;
            node(int t_wordid = 0) :wordid(t_wordid), file(new filelist(t_wordid)), next(nullptr) {}
            ~node()
            {
                if(file)
                    delete file;
            }
        };
        typedef node* storetype;
        typedef filelist* content;
    public:

        hashtable(int tn = 1024);
        ~hashtable();
        hashtable(const hashtable&) = delete;
        hashtable& operator= (const hashtable&) = delete;
        hashtable(hashtable&&) = delete;
        hashtable& operator= (hashtable&&) = delete;

        content insert(const elemtype& elem);
        content search(const elemtype&);
        inline int size()
        {
            return now_size;
        }
        unsigned int hash(const CharString&);

        void rehash(unsigned int new_max_size);
    private:
        unsigned int max_size;
        unsigned int now_size;
        storetype* heap;

        std::hash<std::string> getkey;
    };
}