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
    void Delete(std::string target);
    
    
    BNode* getRoot() { return root; }
    void deleteHelper(BNode* node, std::string& key);
    void destructHelper(BNode* node);
    void searchHelper(BNode* node, const std::string& target, std::vector<Person*>& results);
    void insert(Person* person, const std::string& key);

    void removeFromLeaf(BNode* node, int index);
    void removeFromNonLeaf(BNode* node, int index);
    void merge(BNode* node, int index);
    void fill(BNode* node, int index);
    std::string getPredecessor(BNode* node, int index);
    std::string getSuccessor(BNode* node, int index);
    void borrowFromNext(BNode* node, int index);
    void borrowFromPrev(BNode* node, int index);
};

#endif