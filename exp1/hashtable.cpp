#include <string>
#include "hashtable.h"

ds::hashtable::hashtable(int tn) :max_size(tn), now_size(0)
{
    heap = new storetype[tn];
    for (int i = 0; i < max_size; i++)
        heap[i] = nullptr;
}

ds::hashtable::~hashtable()
{
    for (int i = 0; i < max_size; i++)
        if (heap[i]) {
            node* p(heap[i]);
            while (p) {
                node* temp(p->next);
                delete p;
                p = temp;
            }
        }
    if(heap)
        delete[] heap;
}

//插入某个元素，返回其存储的内容
//如果哈希表存储因子过大，则调整空间rehash
ds::hashtable::content ds::hashtable::insert(const elemtype & elem)
{
    if (now_size * 2 > max_size)//如果存储因子大于0.5
        rehash(2 * max_size);//表长增加一倍
    //首先查看是否已经存在
    auto p = search(elem);
    if (p)
        return p;
    //若不存在，插入
    auto key = hash(elem) % max_size;//计算哈希值
    auto newnode = new node(++now_size);
    newnode->word = elem;
    auto place = heap[key];
    if (place == nullptr) {
        heap[key] = newnode;
        return newnode->file;
    }
    while (place->next)
        place = place->next;
    place->next = newnode;
    return  newnode->file;
}

//查找某个值，如果存在返回其文档链表指针
//如果不存在返回nullptr
ds::hashtable::content ds::hashtable::search(const elemtype& elem)
{
    auto key = hash(elem) % max_size;//计算哈希值
    auto p = heap[key];
    while (p) {
        if (p->word == elem)
            return p->file;
        p = p->next;
    }
    return nullptr;
}

unsigned int ds::hashtable::hash(const CharString & elem)
{
    return getkey(elem.cpp_str());
}

//重新hash
void ds::hashtable::rehash(unsigned int new_max_size)
{
    auto new_heap = new storetype[new_max_size];
    for (int i = 0; i < new_max_size; i++)
        new_heap[i] = nullptr;

    for (int i = 0; i < max_size; i++) {
        while (heap[i]) {
            auto key = hash(heap[i]->word) % new_max_size;
            auto next = heap[i]->next;
            heap[i]->next = nullptr;
            if (new_heap[key] == nullptr)
                new_heap[key] = heap[i];
            else {
                auto temp(new_heap[key]);
                while (temp->next)
                    temp = temp->next;
                temp->next = heap[i];
            }
            heap[i] = next;
        }
    }
    max_size = new_max_size;
    if (heap)
        delete[] heap;
    heap = new_heap;
}
