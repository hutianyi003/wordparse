#pragma once

namespace ds {
    //filelist�����ڴ洢�ĵ�����
    //������ӡ����½��
    //���ݳ��ִ�����������
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
        filelist& operator= (const filelist& rhs) = delete;//��ʽ��ֹ=�����
        filelist(filelist&& rhs);
        filelist& operator= (filelist&& rhs) = delete;//��ʽ��ֹ=�����

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