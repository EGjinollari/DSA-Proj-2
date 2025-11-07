#ifndef BNODE_H
#define BNODE_H

#include <vector>
#include <string>
#include "../person.h"

class BNode {
private:
    bool leaf;
    int degree;
    std::vector<std::string> keys;
    std::vector<Person*> persons;
    std::vector<BNode*> children;

public:
    BNode(int degree, bool leaf);
    ~BNode();
    
    BNode* search(const std::string& key);
    void insertNonFull(Person* person, const std::string& key);
    void splitChild(int i, BNode* y);
    
    bool isLeaf() { return leaf; }
    int getKeyCount() { return keys.size(); }
    std::string getKey(int index) { return keys[index]; }
    Person* getPerson(int index) { return persons[index]; }
    BNode* getChild(int index) { return children[index]; }
    
    friend class BTree;
};

#endif