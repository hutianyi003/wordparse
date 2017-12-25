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

//����洢��������ϣ��
bool retrieve::init(const std::string & inputfile)
{
    std::ifstream input(inputfile);
    if (!input)
        return false;
    std::string buffer;
    std::getline(input, buffer);//���Ե�һ����Ŀ
    for (int i = 0; i < pagenumber; i++) {
        std::getline(input, buffer);
        //���ȶ�ȡ�ִ����ݣ��Ӻ���ǰ�ҵڶ�������
        int end = buffer.length();
        std::string content;
        for (int i = end - 2; i >= 0; i--) {
            if (buffer[i] == '\"') {
                content = buffer.substr(i + 1, end - 2 - i);
                break;
            }
        }
        //�ֳ�ÿ�����ʣ�������ϣ��
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

//����������ѯ
//ָ�������ļ���������ļ���
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

//���ݵ���ָ���ѯ
std::string retrieve::search(ds::CharString index)
{
    ds::CharStringLink store;
    divide(store, index);//�ִ�
    int n = store.size();
    anslist l;
    for (int i = 0; i < n; i++) {
        find(store.get(i), l);
    }
    l.sort();
    return l.str();
}

//���ݵ������ʲ�ѯ���
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

//�ִ��㷨
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

//����ĳ����ַ
//ָ��urlid�͹ؼ��ʳ��ֵĴ���
void retrieve::anslist::add(int t_fileid, int t_occurs_times)
{
    node* p(head);
    for (int i = 0; i < now_size; i++) {
        if (p->fileid == t_fileid) {//ԭ���ʹ���
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

//����˳��ʹ�ý������
void retrieve::anslist::sort()
{
    //ע�⣺Ԫ����������Ҫ����Ĺؼ��֣����ȼ��Ӹߵ���Ϊ��occurs_word > occurs_times > fileid

    nodelink* temp = new nodelink[now_size];//��ʱ����ÿ��ָ����������
    nodelink p(head);
    for (int i = 0; i < now_size; i++) {
        temp[i] = p;
        p = p->next;
    }
    //ʹ��ð��������ΪԪ�ظ���һ�㲻�ᳬ��100
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

//�����ַ������
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
