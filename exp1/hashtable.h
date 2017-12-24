#pragma once

#include <string>

#include "CharString.h"
#include "filelist.h"

namespace ds {
    /*
    基于链表解决冲突的一个哈希实现
    哈希元素为自定义的字符串类型
    */
    class hashtable {
    private:
        //存储类型定义

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

        //指定初始表长，默认为1024
        hashtable(int tn = 1024);
        ~hashtable();
        //不允许复制或移动
        hashtable(const hashtable&) = delete;
        hashtable& operator= (const hashtable&) = delete;
        hashtable(hashtable&&) = delete;
        hashtable& operator= (hashtable&&) = delete;

        //插入某个元素，返回其存储的内容
        //如果哈希表存储因子过大，则调整空间rehash
        content insert(const elemtype& elem);

        //查找某个值，如果存在返回其文档链表指针
        //如果不存在返回nullptr
        content search(const elemtype& elem);

        //返回目前哈希表元素个数
        inline int size()
        {
            return now_size;
        }

        //用于计算哈希值
        unsigned int hash(const CharString&);

        void rehash(unsigned int new_max_size);
    private:
        unsigned int max_size;//表长
        unsigned int now_size;//元素个数
        storetype* heap;

        std::hash<std::string> getkey;//用于实现哈希函数
    };
}