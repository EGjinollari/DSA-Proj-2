#include "btree.h"
#include <iostream>

using namespace std;

BTree::BTree(int deg) {
    this->deg = deg;
    root = nullptr;
}

BTree::~BTree() {
    destructHelper(root);
}

void BTree::destructHelper(BNode* node) {
    if (!node) {
        return;
    }
    if (!node->isLeaf()) {
        for (int i = 0; i <= node->getKeyCount(); i++) {
            destructHelper(node->getChild(i));
        }
    }
    delete node;
}

void BTree::searchHelper(BNode* node, const string& target, vector<Person*>& results) {
    if (!node) {
        return;
    }
    
    int i = 0;
    while (i < node->getKeyCount()) {
        if (target > node->getKey(i)) {
            i++;
        } else if (node->getKey(i) == target) {
            results.push_back(node->getPerson(i));
            i++;
        } else {
            break;
        }
    }
    
    if (!node->isLeaf()) {
        searchHelper(node->getChild(i), target, results);
    }
}

void BTree::insert(Person* person, const string& key) {
    if (!root) {
        root = new BNode(deg, true);
        root->addKey(key);
        root->addPerson(person);
    } else {
        if (root->getKeyCount() == 2 * deg - 1) {
            BNode* s = new BNode(deg, false);
            s->addChild(root);
            s->splitChild(0, root);
            
            int i = 0;
            if (key > s->getKey(0)) {
                i = 1;
            } else {
                i = 0;
            }
            s->getChild(i)->insertNonFull(person, key);
            
            root = s;
        } else {
            root->insertNonFull(person, key);
        }
    }
}

void BTree::removeFromLeaf(BNode* node, int index){
    delete node->getPerson(index);
    node->removeKey(index);
    node->removePerson(index);
}

void BTree::removeFromNonLeaf(BNode* node, int index){
    string key = node->getKey(index);

    int left_child_keys = node->getChild(index)->getKeyCount();
    if (left_child_keys >= deg){
        string pred = getPredecessor(node, index);
        node->setKey(index, pred);
        deleteHelper(node->getChild(index), pred);
    }
    else {
        int right_child_keys = node->getChild(index + 1)->getKeyCount();
        if (right_child_keys >= deg){
            string succ = getSuccessor(node, index);
            node->setKey(index, succ);
            deleteHelper(node->getChild(index + 1), succ);
        }
        else{
            merge(node, index);
            deleteHelper(node->getChild(index), key);
        }
    }
}

string BTree::getPredecessor(BNode* node, int index){
    BNode* curr = node->getChild(index);
    while(!curr->isLeaf()){
        curr = curr->getChild(curr->getKeyCount());
    }
    return curr->getKey(curr->getKeyCount() - 1);
}

string BTree::getSuccessor(BNode* node, int index){
    BNode* curr = node->getChild(index + 1);
    while(!curr->isLeaf()){
        curr = curr->getChild(0);
    }
    return curr->getKey(0);
}

void BTree::merge(BNode* node, int index){
    BNode* child = node->getChild(index);
    BNode* sib = node->getChild(index + 1);

    child->addKey(node->getKey(index));
    child->addPerson(node->getPerson(index));

    for (int i = 0; i < sib->getKeyCount(); i++){
        child->addKey(sib->getKey(i));
        child->addPerson(sib->getPerson(i));
    }

    if (!child->isLeaf()){
        for (int i = 0; i <= sib->getKeyCount(); i++){
            child->addChild(sib->getChild(i));
        }
    }

    node->removeKey(index);
    node->removePerson(index);
    node->removeChild(index + 1);
    sib->clearPersons();
    delete sib;
}

void BTree::transferPrev(BNode* node, int index){
    BNode* child = node->getChild(index);
    BNode* sib = node->getChild(index - 1);
    child->insertKey(0, node->getKey(index - 1));
    child->insertPerson(0, node->getPerson(index - 1));
    node->setKey(index - 1, sib->getKey(sib->getKeyCount() - 1));
    node->setPerson(index - 1, sib->getPerson(sib->getKeyCount() - 1));

    if (!child->isLeaf()){
        child->insertChild(0, sib->getChild(sib->getKeyCount()));
    }

    sib->popBackKey();
    sib->popBackPerson();

    if (!sib->isLeaf()){
        sib->popBackChild();
    }
}

void BTree::transferNext(BNode* node, int index){
    BNode* child = node->getChild(index);
    BNode* sib = node->getChild(index + 1);
    child->addKey(node->getKey(index));
    child->addPerson(node->getPerson(index));
    node->setKey(index, sib->getKey(0));
    node->setPerson(index, sib->getPerson(0));

    if (!child->isLeaf()){
        child->addChild(sib->getChild(0));
    }

    sib->removeKey(0);
    sib->removePerson(0);
    
    if(!sib->isLeaf()){
        sib->removeChild(0);
    }
}

void BTree::deleteHelper(BNode* node, string& key){
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
        bool inSub = (index == node->getKeyCount());
        if(node->getChild(index)->getKeyCount() < deg){
            fill(node, index);
        }
        if(inSub && index > node->getKeyCount()){
            deleteHelper(node->getChild(index - 1), key);
        }
        else{
            deleteHelper(node->getChild(index), key);
        }
    }
    
}

void BTree::Delete(string target) {
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

void BTree::fill(BNode* node, int index){
    if (index != 0 && node->getChild(index - 1)->getKeyCount() > deg){
        transferPrev(node, index);
    }
    else if (index != node->getKeyCount() && node->getChild(index + 1)->getKeyCount() >= deg){
        transferNext(node, index);
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