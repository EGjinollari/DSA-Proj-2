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
    // Constructor and Destructor
    BTree(int deg);
    virtual ~BTree();
    // Insert / Search / Delete
    virtual void Insert(int id, string fn, string ln, int bday, string origin, string dest) = 0;
    virtual vector<Person*> Search(string val) = 0;
    void Delete(string target);
    
    // Root Getter
    BNode* getRoot() { return root; }

    // Recursive helper functions
    void deleteHelper(BNode* node, string& key);
    void destructHelper(BNode* node);
    void searchHelper(BNode* node, const string& target, vector<Person*>& results);
    
    // Functions to maintain Btree properties
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