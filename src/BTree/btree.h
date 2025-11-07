#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <unordered_set>
#include <string>
#include "bnode.h"

class BTree {
protected:
    BNode* root;
    int degree;
    std::unordered_set<int> taken_ids;

public:
    BTree(int degree);
    virtual ~BTree();
    
    virtual void Insert(int id, std::string fn, std::string ln, int bday, 
                       std::string origin, std::string dest) = 0;
    virtual std::vector<Person*> Search(std::string val) = 0;
    virtual void Delete(std::string target) = 0;
    
    BNode* getRoot() { return root; }
    void destructHelper(BNode* node);
    void searchHelper(BNode* node, const std::string& target, std::vector<Person*>& results);
    void insert(Person* person, const std::string& key);
};

#endif