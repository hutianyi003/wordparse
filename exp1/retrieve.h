#pragma once

#include "CharStringLink.h"
#include "hashtable.h"
#include "wordParse.h"

class retrieve {
private:
    //自定义用于整理结果的数据结构
    class node {
    public:
        int occurs_word;
        int fileid;
        int occurs_times;
        node* next;
        node() :next(nullptr) {}
    };
    class anslist {
        typedef node* nodelink;
    public:
        anslist();
        ~anslist();
        //增加某个网址
        //指明urlid和关键词出现的次数
        void add(int t_fileid, int t_occurs_times);

        //调整顺序使得结果有序
        void sort();
        bool smaller(nodelink, nodelink);

        //返回字符化结果
        std::string str();

        inline int size()
        {
            return now_size;
        }
    private:
        node * head;
        int now_size;

    };

public:
    //指定页面数和哈希表表长
    retrieve(int t_pagenumber = 0, int hashlenth = 1024);
    ~retrieve();

    retrieve(const retrieve&) = delete;
    retrieve(retrieve&&) = delete;
    retrieve& operator= (const retrieve&) = delete;
    retrieve& operator= (retrieve&&) = delete;

    //载入存储容器（哈希表）
    bool init(const std::string& inputfile);

    //进行批量查询
    //指定输入文件名和输出文件名
    bool exec(const std::string& inputfile, const std::string& outputfile);

    //根据单条指令查询
    std::string search(ds::CharString index);

    //根据单个单词查询
    void find(ds::CharString word, anslist& store);
private:
    int pagenumber;
    ds::hashtable* table;
    wordParse* word;
    static const int MaxDivideLenth = 5;//max word lenth
	bool divide(ds::CharStringLink& store, const ds::CharString& context);
};

ds::CharStringLink* getword();