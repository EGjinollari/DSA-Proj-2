#ifndef LNTREE_H
#define LNTREE_H

#include "btree.h"
#include <vector>

class LNTree : public BTree {
public:
    LNTree(int degree = 3) : BTree(degree) {}
    
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest) override;
    
    std::vector<Person*> Search(std::string val) override;
    void Delete(std::string target) override;
};

#endif