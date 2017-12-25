#pragma once

#include "CharStringLink.h"
#include "hashtable.h"
#include "wordParse.h"

class retrieve {
private:
    //�Զ������������������ݽṹ
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
        //����ĳ����ַ
        //ָ��urlid�͹ؼ��ʳ��ֵĴ���
        void add(int t_fileid, int t_occurs_times);

        //����˳��ʹ�ý������
        void sort();
        bool smaller(nodelink, nodelink);

        //�����ַ������
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
    //ָ��ҳ�����͹�ϣ���
    retrieve(int t_pagenumber = 0, int hashlenth = 1024);
    ~retrieve();

    retrieve(const retrieve&) = delete;
    retrieve(retrieve&&) = delete;
    retrieve& operator= (const retrieve&) = delete;
    retrieve& operator= (retrieve&&) = delete;

    //����洢��������ϣ��
    bool init(const std::string& inputfile);

    //����������ѯ
    //ָ�������ļ���������ļ���
    bool exec(const std::string& inputfile, const std::string& outputfile);

    //���ݵ���ָ���ѯ
    std::string search(ds::CharString index);

    //���ݵ������ʲ�ѯ
    void find(ds::CharString word, anslist& store);
private:
    int pagenumber;
    ds::hashtable* table;
    wordParse* word;
    static const int MaxDivideLenth = 5;//max word lenth
	bool divide(ds::CharStringLink& store, const ds::CharString& context);
};

ds::CharStringLink* getword();