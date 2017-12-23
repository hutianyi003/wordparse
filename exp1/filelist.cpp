#include "filelist.h"

void ds::adjust(ds::filelist*, ds::filelist::node*);

ds::filelist::filelist(int t_wordid) :head(nullptr), now_size(0), wordid(t_wordid)
{
}

//�������������ͷ�ÿ��node�Ŀռ�
ds::filelist::~filelist()
{
    node* p = head;
    while (p) {
        node* next(p->next);
        delete p;
        p = next;
    }
    return;
}

//�������캯�����θ���ÿ������
ds::filelist::filelist(const filelist & rhs)
{
    node* p = rhs.head;
    node* temphead = nullptr;
    node* temptail = nullptr;
    while (p) {
        node* next(p->next);
        node* now(new node(p->fileid, p->d));
        if (temphead == nullptr) {
            temphead = now;
            temptail = now;
        }
        else {
            temptail->next = now;
            temptail = now;
        }
    }
    head = temphead;
    now_size = rhs.now_size;
}

ds::filelist::filelist(filelist && rhs) :head(rhs.head), now_size(rhs.now_size) 
{
    rhs.head = nullptr;
    rhs.now_size = 0;
}

inline bool bigger(const ds::filelist::node* x, const ds::filelist::node* y)
{
    if (x->d == y->d)
        return x->fileid < y->fileid;
    return x->d > y->d;
}

//������������
void ds::adjust(ds::filelist* toadjust, ds::filelist::node* p)
{
    //���Ƚ�pָ��Ľ���������ȥ��
    if (toadjust->head == p)
        toadjust->head = toadjust->head->next;
    else {
        ds::filelist::node* h = toadjust->head;
        while (h->next != p) {
            h = h->next;
        }
        h->next = h->next->next;
    }
    //���½�p���뵽���ʵ�λ��
    if (bigger(p, toadjust->head)) {
        ds::filelist::node* temp(toadjust->head);
        toadjust->head = p;
        p->next = temp;
        return;
    }
    ds::filelist::node* start = toadjust->head;
    while (start) {
        if (start->next == nullptr || bigger(p, start->next)) {
            ds::filelist::node* temp(start->next);
            start->next = p;
            p->next = temp;
            break;
        }
        start = start->next;
    }
    return;
}
//���ĵ����������ĳ���ĵ��ڵ�
//�������򷵻�true������Ѵ�����ʹ�ô���+1������false
bool ds::filelist::add(int t_fileid)
{
    if (head == nullptr) {
        head = new node(t_fileid);
        now_size = 0;
        return true;
    }
    node* p = head;
    node* last = nullptr;
    while (p) {
        //������ڣ�����ִ���+1���ҵ���˳��
        if (p->fileid == t_fileid) {
            (p->d)++;
            //adjust
            adjust(this, p);
            return false;
        }
        last = p;
        p = p->next;
    }
    //������
    last->next = new node(t_fileid);
    adjust(this, last->next);
    now_size++;
    return true;
}

//�༭ĳ���ĵ����������ڷ���false
bool ds::filelist::edit(int t_fileid, storetype td)
{
    node* p = head;
    while (p) {
        if (p->fileid == t_fileid) {
            p->d = td;
            adjust(this, p);
            return true;
        }
        p = p->next;
    }
    return false;
}

//Ѱ��ĳ���ĵ���Ӧ�Ĵ���
//�������ڷ���noexist
ds::filelist::storetype ds::filelist::search(int t_fileid)
{
    node* p = head;
    while (p) {
        if (p->fileid == t_fileid)
            return p->d;
        p = p->next;
    }
    return ds::filelist::noexist;
}

//ɾ��ĳ��id���ĵ���¼
//�������ڷ���false
bool ds::filelist::remove(int t_fileid)
{
    node* p = head;
    node* last = nullptr;
    while (p) {
        if (p->fileid == t_fileid) {
            if(!last)
                head = p->next;
            else
                last->next = p->next;
            delete p;
            now_size--;
            return true;
        }
        last = p;
        p = p->next;
    }
    return false;
}
