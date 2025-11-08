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

void BTree::removeFromLeaf(BNode* node, int index){
    delete node->persons[index];
    node->keys.erase(node->keys.begin() + index);
    node->persons.erase(node->persons.begin() + index);
}


void BTree::removeFromNonLeaf(BNode* node, int index){
    auto key = node->getKey(index);

    if (node->getChild(index)->getKeyCount() >= degree){
        auto pred = getPredecessor(node, index);
        node->keys[index] = pred;
        deleteHelper(node->getChild(index), pred);
    }
    else if (node->getChild(index + 1)->getKeyCount() >= degree){
        auto succ = getSuccessor(node, index);
        node->keys[index] = succ;
        deleteHelper(node->getChild(index + 1), succ);
    }
    else{
        merge(node, index);
        deleteHelper(node->getChild(index), key);
    }
}

std::string BTree::getPredecessor(BNode* node, int index){
    BNode* current = node->getChild(index);
    while(!current->isLeaf()){
        current = current->getChild(current->getKeyCount());
    }
    return current->getKey(current->getKeyCount() - 1);
}

std::string BTree::getSuccessor(BNode* node, int index){
    BNode* current = node->getChild(index + 1);
    while(!current->isLeaf()){
        current = current->getChild(0);
    }
    return current->getKey(0);
}

void BTree::merge(BNode* node, int index){
    BNode* child = node->getChild(index);
    BNode* sib = node->getChild(index + 1);

    child->keys.push_back(node->getKey(index));
    child->persons.push_back(node->getPerson(index));

    for (int i = 0; i < sib->getKeyCount(); i++){
        child->keys.push_back(sib->getKey(i));
        child->persons.push_back(sib->getPerson(i));
    }

    if (!child->isLeaf()){
        for (int i = 0; i <= sib->getKeyCount(); i++){
            child->children.push_back(sib->getChild(i));
        }
    }

    node->keys.erase(node->keys.begin() + index);
    node->persons.erase(node->persons.begin() + index);
    node->children.erase(node->children.begin() + index + 1);
    sib->persons.clear();
    delete sib;
}

void BTree::fill(BNode* node, int index){
    if (index != 0 && node->getChild(index - 1)->getKeyCount() >= degree){
        borrowFromPrev(node, index);
    }
    else if (index != node->getKeyCount() && node->getChild(index + 1)->getKeyCount() >= degree){
        borrowFromNext(node, index);
    }
    else{
        if (index != node->getKeyCount()){
            merge(node, index);
        }
        else{
            merge(node, index - 1);
        }
    }
}

void BTree::borrowFromPrev(BNode* node, int index){
    BNode* child = node->getChild(index);
    BNode* sib = node->getChild(index - 1);

    child->keys.insert(child->keys.begin(), node->getKey(index - 1));
    child->persons.insert(child->persons.begin(), node->getPerson(index - 1));

    node->keys[index - 1] = sib->getKey(sib->getKeyCount() - 1);
    node->persons[index - 1] = sib->getPerson(sib->getKeyCount() - 1);

    if (!!child->isLeaf()){
        child->children.insert(child->children.begin(), sib->getChild(sib->getKeyCount()));
    }

    sib->keys.pop_back();
    sib->persons.pop_back();
    if (!sib->isLeaf()){
        sib->children.pop_back();
    }
}

void BTree::borrowFromNext(BNode* node, int index){
    BNode* child = node->getChild(index);
    BNode* sib = node->getChild(index + 1);

    child->keys.push_back(node->getKey(index));
    child->persons.push_back(node->getPerson(index));
    node->keys[index] = sib->getKey(0);
    node->persons[index] = sib->getPerson(0);

    if (!child->isLeaf()){
        child->children.push_back(sib->getChild(0));
    }

    sib->keys.erase(sib->keys.begin());
    sib->persons.erase(sib->persons.begin());
    
    if(!sib->isLeaf()){
        sib->children.erase(sib->children.begin());
    }

}

void BTree::deleteHelper(BNode* node, std::string& key){
    int index = 0;
    while (index < node->getKeyCount() && node->getKey(index) < key){
        index ++;
    }

    if(index < node->getKeyCount() && node->getKey(index) == key){
        if (node->isLeaf()){
            removeFromLeaf(node, index);
        }
        else{
            removeFromNonLeaf(node, index);
        }
    }
    else{
        if(node->isLeaf()){
            return;
        }
    }
    bool inSub = (index == node->getKeyCount());
    if(node->getChild(index)->getKeyCount() < degree){
        fill(node, index);
    }
    if(inSub && index > node->getKeyCount()){
        deleteHelper(node->getChild(index - 1), key);
    }
    else{
        deleteHelper(node->getChild(index), key);
    }
}

void BTree::Delete(std::string target) {
    if (!root){
        return;
    }


    deleteHelper(root, target);

    if (root->getKeyCount() == 0){
        BNode* temp = root;
        if (root->isLeaf()){
            root = nullptr;
        }
        else{
            root = root->getChild(0);
        }
        delete temp;
    }
}