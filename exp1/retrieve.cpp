#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "retrieve.h"

retrieve::retrieve(int t_pagenumber, int hashlenth):
    pagenumber(t_pagenumber),
    table(new ds::hashtable(hashlenth)),
    word(new wordParse)
{
    std::cout << "Loading dictionary..." << std::endl;
    word->getDic("common.dic");
    word->getSpdic("sp.dic");
}

retrieve::~retrieve()
{
    delete table;
    delete word;
}

//载入存储容器（哈希表）
bool retrieve::init(const std::string & inputfile)
{
    std::ifstream input(inputfile);
    if (!input)
        return false;
    std::string buffer;
    std::getline(input, buffer);//忽略第一行条目
    for (int i = 0; i < pagenumber; i++) {
        std::getline(input, buffer);
        //首先读取分词内容，从后往前找第二个引号
        int end = buffer.length();
        std::string content;
        for (int i = end - 2; i >= 0; i--) {
            if (buffer[i] == '\"') {
                content = buffer.substr(i + 1, end - 2 - i);
                break;
            }
        }
        //分出每个单词，构建哈希表
        int wordstart = 0;
        int len = content.length();
        while (wordstart < len) {
            int wordend = wordstart + 1;
            while (wordend < len&&content[wordend] != ' ')
                wordend++;
            auto f = table->insert(content.substr(wordstart, wordend - wordstart));
            f->add(i + 1);
            wordstart = wordend + 1;
        }
    }
    return true;
}

//进行批量查询
//指定输入文件名和输出文件名
bool retrieve::exec(const std::string & inputfile, const std::string & outputfile)
{
    std::ifstream input(inputfile);
    std::ofstream output(outputfile);
    std::cout << "Start query search!\n";
    if (!input)
        return false;
    std::string buffer;
    int n = 0;
    while (std::getline(input, buffer)) {
        std::cout << "Searching line " << ++n << std::endl;
        output << search(buffer) << std::endl;
    }
    
    std::cout << "\nDone!\n";
    return true;
}

//根据单条指令查询
std::string retrieve::search(ds::CharString index)
{
    ds::CharStringLink store;
    divide(store, index);//分词
    int n = store.size();
    anslist l;
    for (int i = 0; i < n; i++) {
        find(store.get(i), l);
    }
    l.sort();
    return l.str();
}

//根据单个单词查询结果
void retrieve::find(ds::CharString word, anslist& store)
{
    auto file = table->search(word);
    if (file == nullptr)
        return;
    int n = file->size();
    auto now = file->head;
    for (int i = 0; i < n; i++) {
        store.add(now->fileid, now->d);
        now = now->next;
    }
    return;
}

//分词算法
bool retrieve::divide(ds::CharStringLink & store, const ds::CharString & context)
{
	int len = context.len();
	for (int i = 0; i < len; i++) {
		// parse numbers
		if (isdigit(context[i])) {
			int addlen = 1;
			while (isdigit(context[i + addlen])) {
				addlen++;
			}
			store.add(context.substring(i, addlen));
			i += (addlen - 1);
		}
		// from max lenth to parse words
		for (int j = MaxDivideLenth; j > 0; j--) {
			if (i + j * 2 > len)
				continue;
			ds::CharString cut = context.substring(i, j * 2);
			if (word->exist(cut.cpp_str()))
			{
				store.add(cut);
				i += (2 * j - 1);
			}
		}
	}
	return true;
}

retrieve::anslist::anslist() :now_size(0), head(nullptr)
{
}

retrieve::anslist::~anslist()
{
    while(head){
        node* temp(head->next);
        delete head;
        head = temp;
    }
}

//增加某个网址
//指明urlid和关键词出现的次数
void retrieve::anslist::add(int t_fileid, int t_occurs_times)
{
    node* p(head);
    for (int i = 0; i < now_size; i++) {
        if (p->fileid == t_fileid) {//原本就存在
            p->occurs_word++;
            p->occurs_times += t_occurs_times;
            return;
        }
        if (i != now_size - 1)
            p = p->next;
    }
    now_size++;
    node* temp = new node;
    temp->fileid = t_fileid;
    temp->occurs_word = 1;
    temp->occurs_times = t_occurs_times;
    if (head == nullptr)
        head = temp;
    else
        p->next = temp;
}

//调整顺序使得结果有序
void retrieve::anslist::sort()
{
    //注意：元素有三个需要排序的关键字，优先级从高到底为：occurs_word > occurs_times > fileid

    nodelink* temp = new nodelink[now_size];//临时保存每个指针用于排序
    nodelink p(head);
    for (int i = 0; i < now_size; i++) {
        temp[i] = p;
        p = p->next;
    }
    //使用冒泡排序，因为元素个数一般不会超过100
    for (int i = 0; i < now_size - 1; i++)
        for (int j = 0; j < now_size - i - 1; j++)
            if (smaller(temp[j], temp[j + 1])) {
                std::swap(temp[j], temp[j + 1]);
            }
    for (int i = 0; i < now_size - 1; i++)
        temp[i]->next = temp[i + 1];
    temp[now_size - 1]->next = nullptr;
    head = temp[0];
    delete[] temp;
}

inline bool retrieve::anslist::smaller(nodelink x, nodelink y)
{
    if (x->occurs_word < y->occurs_word)
        return true;
    else if (x->occurs_word > y->occurs_word)
        return false;
    if (x->occurs_times < y->occurs_times)
        return true;
    else if (x->occurs_times > y->occurs_times)
        return false;
    return x->fileid > y->fileid;
}

//返回字符化结果
std::string retrieve::anslist::str()
{
    std::stringstream s;
    nodelink p(head);
    for (int i = 0; i < now_size; i++) {
        s.put('(');
        s << p->fileid;
        s.put(',');
        s << p->occurs_times;
        s.put(')');
        if (i != now_size - 1)
            s.put(' ');
        p = p->next;
    }
    return s.str();
}
