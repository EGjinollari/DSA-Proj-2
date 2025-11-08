#pragma once

#include <vector>
#include <unordered_set>
#include <string>
#include "bnode.h"

using namespace std;

class BTree {
protected:
    BNode* root;
    int deg;
    unordered_set<int> taken_ids;

public:
    BTree(int deg);
    virtual ~BTree();
    virtual void Insert(int id, string fn, string ln, int bday, string origin, string dest) = 0;
    virtual vector<Person*> Search(string val) = 0;
    void Delete(string target);
    BNode* getRoot() { return root; }
    void deleteHelper(BNode* node, string& key);
    void destructHelper(BNode* node);
    void searchHelper(BNode* node, const string& target, vector<Person*>& results);
    void insert(Person* person, const string& key);
    void removeFromLeaf(BNode* node, int index);
    void removeFromNonLeaf(BNode* node, int index);
    void merge(BNode* node, int index);
    void fill(BNode* node, int index);
    string getPredecessor(BNode* node, int index);
    string getSuccessor(BNode* node, int index);
    void transferNext(BNode* node, int index);
    void transferPrev(BNode* node, int index);
};