#pragma once

#include "../btree.h"
#include <vector>

using namespace std;

class DESTree : public BTree {
public:
    DESTree(int degree = 10) : BTree(degree) {}
    
    void Insert(int id, string fn, string ln, int bday, string origin, string dest) override;
    
    vector<Person*> Search(string val) override;
};