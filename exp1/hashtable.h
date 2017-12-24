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
    private:
        //�洢���Ͷ���

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

        //ָ����ʼ����Ĭ��Ϊ1024
        hashtable(int tn = 1024);
        ~hashtable();
        //�������ƻ��ƶ�
        hashtable(const hashtable&) = delete;
        hashtable& operator= (const hashtable&) = delete;
        hashtable(hashtable&&) = delete;
        hashtable& operator= (hashtable&&) = delete;

        //����ĳ��Ԫ�أ�������洢������
        //�����ϣ��洢���ӹ���������ռ�rehash
        content insert(const elemtype& elem);

        //����ĳ��ֵ��������ڷ������ĵ�����ָ��
        //��������ڷ���nullptr
        content search(const elemtype& elem);

        //����Ŀǰ��ϣ��Ԫ�ظ���
        inline int size()
        {
            return now_size;
        }

        //���ڼ����ϣֵ
        unsigned int hash(const CharString&);

        void rehash(unsigned int new_max_size);
    private:
        unsigned int max_size;//��
        unsigned int now_size;//Ԫ�ظ���
        storetype* heap;

        std::hash<std::string> getkey;//����ʵ�ֹ�ϣ����
    };
}