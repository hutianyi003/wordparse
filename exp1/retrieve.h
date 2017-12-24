#pragma once

#include "CharStringLink.h"
#include "hashtable.h"

class retrieve {
public:
    retrieve(int t_pagenumber = 0, int hashlenth = 1024);
    ~retrieve();

    retrieve(const retrieve&) = delete;
    retrieve(retrieve&&) = delete;
    retrieve& operator= (const retrieve&) = delete;
    retrieve& operator= (retrieve&&) = delete;

    bool init(const std::string& inputfile, const std::string& outputfile);
    bool exec(const std::string& inputfile, const std::string& outputfile);
    std::string search(ds::CharString& index);
private:
    int pagenumber;
    ds::hashtable table;
    std::string inputfile;
    std::string outputfile;
};

ds::CharStringLink* getword();