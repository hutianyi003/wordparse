#include "filelist.h"

void ds::adjust(ds::filelist*, ds::filelist::node*);

ds::filelist::filelist(int t_wordid) :head(nullptr), now_size(0), wordid(t_wordid)
{
}

//析构函数依次释放每个node的空间
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

//拷贝构造函数依次复制每个链表
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

//修正保持有序
void ds::adjust(ds::filelist* toadjust, ds::filelist::node* p)
{
    //首先将p指向的结点从链表中去除
    if (toadjust->head == p)
        toadjust->head = toadjust->head->next;
    else {
        ds::filelist::node* h = toadjust->head;
        while (h->next != p) {
            h = h->next;
        }
        h->next = h->next->next;
    }
    //重新将p插入到合适的位置
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
//在文档链表中添加某个文档节点
//如果添加则返回true，如果已存在则使得次数+1，返回false
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
        //如果存在，则出现次数+1并且调整顺序
        if (p->fileid == t_fileid) {
            (p->d)++;
            //adjust
            adjust(this, p);
            return false;
        }
        last = p;
        p = p->next;
    }
    //不存在
    last->next = new node(t_fileid);
    adjust(this, last->next);
    now_size++;
    return true;
}

//编辑某个文档，若不存在返回false
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

//寻找某个文档对应的次数
//若不存在返回noexist
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

//删除某个id的文档记录
//若不存在返回false
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
