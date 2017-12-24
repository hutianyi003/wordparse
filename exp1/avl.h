#pragma once

#include "CharString.h"
#include "filelist.h"

namespace ds {
    //平衡二叉树
    //使用自定义的CharString进行索引
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

        //不允许复制或移动
        avl(const avl&) = delete;
        avl(avl&&) = delete;
        avl& operator= (const avl&) = delete;
        avl& operator= (avl&&) = delete;

        //插入某个元素，返回其文档链表的指针
        //如果已存在同样返回指针
        content insert(const elemtype& elem);

        //检索某个元素，返回其文档指针
        //不存在则返回nullptr
        content search(const elemtype& elem);

        //调整avl使其平衡
        bool adjust();

        //删除某个元素，删除成功返回true
        //若原本就不存在则返回false
        bool remove(const elemtype& elem);

        //编辑某个元素，成功返回true
        //若不存在则返回false
        bool edit(const elemtype& elem, storetype newvalue);

    private:
        int now_size;
        storetype root;
        void delNode(storetype p);
    };
}