#pragma once

#include "CharString.h"

namespace ds {
    class avl {
        typedef ds::CharString elemtype;
        typedef int storetype;
    public:
        avl();
        ~avl();
        avl(const avl&) = delete;
        avl(avl&&) = delete;
        avl& operator= (const avl&) = delete;
        avl& operator= (avl&&) = delete;

        bool insert(const elemtype&);
        storetype search(const elemtype&);
        bool adjust();
        bool remove(const elemtype&);
        bool edit(const elemtype&, storetype);
    private:
        int now_size;
    };
}