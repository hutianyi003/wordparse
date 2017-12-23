#pragma once

namespace ds {
    //filelist类用于存储文档链表
    //可以添加、更新结点
    //根据出现次数保持有序
    class filelist {

    public:

        typedef int storetype;
        static const storetype noexist = -1;

        class node {
        public:
            storetype d;
            int fileid;
            node* next;
            node(int t_fileid, storetype td = 1) :fileid(t_fileid), d(td), next(nullptr) {}
        };

    public:
        filelist(int t_wordid = -1);
        ~filelist();
        filelist(const filelist& rhs);
        filelist& operator= (const filelist& rhs) = delete;//显式禁止=运算符
        filelist(filelist&& rhs);
        filelist& operator= (filelist&& rhs) = delete;//显式禁止=运算符

        bool add(int t_fileid);
        bool edit(int t_fileid, storetype td);
        storetype search(int t_fileid);
        bool remove(int t_fileid);

        inline int size() 
        {
            return now_size;
        }

    private:
        node* head;
        int now_size;
        int wordid;
        friend void adjust(filelist*, node*);
        
    };
}