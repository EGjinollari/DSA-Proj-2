#include "btree.h"
#include <iostream>

BTree::BTree(int degree) {
    this->degree = degree;
    root = nullptr;
}

BTree::~BTree() {
    destructHelper(root);
}

void BTree::destructHelper(BNode* node) {
    if (node) {
        if (!node->isLeaf()) {
            for (int i = 0; i <= node->getKeyCount(); i++) {
                destructHelper(node->getChild(i));
            }
        }
        delete node;
    }
}

void BTree::searchHelper(BNode* node, const std::string& target, std::vector<Person*>& results) {
    if (!node) return;
    
    int i = 0;
    while (i < node->getKeyCount() && target > node->getKey(i)) {
        i++;
    }
    
    while (i < node->getKeyCount() && node->getKey(i) == target) {
        results.push_back(node->getPerson(i));
        i++;
    }
    
    if (!node->isLeaf()) {
        searchHelper(node->getChild(i), target, results);
    }
}

void BTree::insert(Person* person, const std::string& key) {
    if (root == nullptr) {
        root = new BNode(degree, true);
        root->keys.push_back(key);
        root->persons.push_back(person);
    } else {
        if (root->keys.size() == 2 * degree - 1) {
            BNode* s = new BNode(degree, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            
            int i = 0;
            if (s->keys[0] < key) {
                i++;
            }
            s->children[i]->insertNonFull(person, key);
            
            root = s;
        } else {
            root->insertNonFull(person, key);
        }
    }
}