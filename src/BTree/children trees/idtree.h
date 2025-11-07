#ifndef IDTREE_H
#define IDTREE_H

#include "btree.h"
#include <vector>

class IDTree : public BTree {
public:
    IDTree(int degree = 3) : BTree(degree) {}
    
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest) override;
    
    std::vector<Person*> Search(std::string val) override;
    void Delete(std::string target) override;
};

#endif