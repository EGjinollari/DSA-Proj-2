#include "bnode.h"
#include <iostream>

using namespace std;
// Constructor / Destructor
BNode::BNode(int deg, bool leaf) {
    this->deg = deg;
    this->leaf = leaf;
}

BNode::~BNode() {
    for (auto person : persons) {
        delete person;
    }
}

// Search for a node
BNode* BNode::search(const string& key) {
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

// Insert into a nonfull node
void BNode::insertNonFull(Person* person, const string& key) {
    int i = keys.size() - 1;
    
    if (leaf) {
        keys.push_back("");
        persons.push_back(nullptr);
        
        for (int j = keys.size() - 2; j >= 0; j--) {
            if (keys[j] > key) {
                keys[j + 1] = keys[j];
                persons[j + 1] = persons[j];
            } else {
                break;
            }
        }
        
        for (int j = 0; j < keys.size(); j++) {
            if (keys[j] == "" || keys[j] > key) {
                keys[j] = key;
                persons[j] = person;
                break;
            }
        }
    } else {
        int pos = 0;
        while (pos < keys.size() && keys[pos] < key) {
            pos++;
        }
        
        if (children[pos]->keys.size() == 2 * deg - 1) {
            splitChild(pos, children[pos]);
            if (keys[pos] < key) {
                pos++;
            }
        }
        children[pos]->insertNonFull(person, key);
    }
}

// Split a node into and move index i to the parent node
void BNode::splitChild(int i, BNode* y) {
    BNode* z = new BNode(y->deg, y->leaf);
    
    for (int j = 0; j < deg - 1; j++) {
        z->keys.push_back(y->keys[deg + j]);
        z->persons.push_back(y->persons[deg + j]);
    }
    
    if (!y->leaf) {
        for (int j = 0; j < deg; j++) {
            z->children.push_back(y->children[deg + j]);
        }
    }
    
    int new_size = deg - 1;
    y->keys.resize(new_size);
    y->persons.resize(new_size);
    if (!y->leaf) {
        y->children.resize(deg);
    }
    
    vector<BNode*> new_children;
    for (int j = 0; j <= i; j++) {
        new_children.push_back(children[j]);
    }
    new_children.push_back(z);
    for (int j = i + 1; j < children.size(); j++) {
        new_children.push_back(children[j]);
    }
    children = new_children;
    
    vector<string> new_keys;
    for (int j = 0; j < i; j++) {
        new_keys.push_back(keys[j]);
    }
    new_keys.push_back(y->keys[deg - 1]);
    for (int j = i; j < keys.size(); j++) {
        new_keys.push_back(keys[j]);
    }
    keys = new_keys;
    
    vector<Person*> new_persons;
    for (int j = 0; j < i; j++) {
        new_persons.push_back(persons[j]);
    }
    new_persons.push_back(y->persons[deg - 1]);
    for (int j = i; j < persons.size(); j++) {
        new_persons.push_back(persons[j]);
    }
    persons = new_persons;
}