#ifndef BDTREE_H
#define BDTREE_H

#include "btree.h"
#include <vector>

class BDTree : public BTree {
public:
    BDTree(int degree = 3) : BTree(degree) {}
    
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest) override;
    
    std::vector<Person*> Search(std::string val) override;
    void Delete(std::string target) override;
    
private:
    void deleteHelper(BNode* node, const std::string& target);
};

#endif