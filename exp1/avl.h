#pragma once

#include "CharString.h"
#include "filelist.h"

namespace ds {
    //ƽ�������
    //ʹ���Զ����CharString��������
    class avl {
    private:
        class node {
        public:
            int wordid;
            int balance;
            CharString word;
            filelist* file;
            node *l, *r;
            node(int t_wordid = -1) :
                wordid(t_wordid),
                balance(0),
                file(new filelist(t_wordid)),
                l(nullptr),
                r(nullptr){}

            ~node()
            {
                delete file;
            }
        };

        typedef ds::CharString elemtype;
        typedef node* storetype;
        typedef filelist* content;
    public:
        avl();
        ~avl();

        //�������ƻ��ƶ�
        avl(const avl&) = delete;
        avl(avl&&) = delete;
        avl& operator= (const avl&) = delete;
        avl& operator= (avl&&) = delete;

        //����ĳ��Ԫ�أ��������ĵ������ָ��
        //����Ѵ���ͬ������ָ��
        content insert(const elemtype& elem);

        //����ĳ��Ԫ�أ��������ĵ�ָ��
        //�������򷵻�nullptr
        content search(const elemtype& elem);

        //����avlʹ��ƽ��
        bool adjust();

        //ɾ��ĳ��Ԫ�أ�ɾ���ɹ�����true
        //��ԭ���Ͳ������򷵻�false
        bool remove(const elemtype& elem);

        //�༭ĳ��Ԫ�أ��ɹ�����true
        //���������򷵻�false
        bool edit(const elemtype& elem, storetype newvalue);

    private:
        int now_size;
        storetype root;
        void delNode(storetype p);
    };
}