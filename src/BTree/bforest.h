#pragma once

#include <vector>
#include <string>
#include "../person.h"
#include "btree.h"

using namespace std;

class BForest {
private:
    BTree* id;
    BTree* fn;
    BTree* ln;
    BTree* bd;
    BTree* ori;
    BTree* des;

public:
    BForest();
    ~BForest();
    
    void Insert(int id, string fn, string ln, int bday, 
                string origin, string dest);
    void Delete(string id);
    vector<Person*> Search(string category, string val);
};