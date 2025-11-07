#include "bnode.h"
#include <iostream>

BNode::BNode(int degree, bool leaf) {
    this->degree = degree;
    this->leaf = leaf;
}

BNode::~BNode() {
    for (auto person : persons) {
        delete person;
    }
}

BNode* BNode::search(const std::string& key) {
    int i = 0;
    while (i < keys.size() && key > keys[i]) {
        i++;
    }
    
    if (i < keys.size() && keys[i] == key) {
        return this;
    }
    
    if (leaf) {
        return nullptr;
    }
    
    return children[i]->search(key);
}

void BNode::insertNonFull(Person* person, const std::string& key) {
    int i = keys.size() - 1;
    
    if (leaf) {
        keys.push_back("");
        persons.push_back(nullptr);
        
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            persons[i + 1] = persons[i];
            i--;
        }
        
        keys[i + 1] = key;
        persons[i + 1] = person;
    } else {
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        
        if (children[i + 1]->keys.size() == 2 * degree - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(person, key);
    }
}

void BNode::splitChild(int i, BNode* y) {
    BNode* z = new BNode(y->degree, y->leaf);
    
    for (int j = 0; j < degree - 1; j++) {
        z->keys.push_back(y->keys[j + degree]);
        z->persons.push_back(y->persons[j + degree]);
    }
    
    if (!y->leaf) {
        for (int j = 0; j < degree; j++) {
            z->children.push_back(y->children[j + degree]);
        }
    }
    
    y->keys.resize(degree - 1);
    y->persons.resize(degree - 1);
    if (!y->leaf) {
        y->children.resize(degree);
    }
    
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[degree - 1]);
    persons.insert(persons.begin() + i, y->persons[degree - 1]);
}