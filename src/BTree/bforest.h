#ifndef BFOREST_H
#define BFOREST_H

#include <vector>
#include <string>
#include "person.h"
#include "btree.h"

class BDTree;
class IDBTree;
class FNBTree;
class LNBTree;
class ORIBTree;
class DESBTree;

class BForest {
private:
    IDBTree* id;
    FNBTree* fn;
    LNBTree* ln;
    BDTree* bd;
    ORIBTree* ori;
    DESBTree* des;

public:
    BForest();
    ~BForest();
    
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest);
    void Delete(std::string id);
    std::vector<Person*> Search(std::string category, std::string val);
};

#endif