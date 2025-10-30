#pragma once
#include "node.h"
#include <vector>

class RBTree {
    private:
    Node* root = nullptr;

    public:

    RBTree(Node* root);
    ~RBTree();
    void Deletion_Helper(Node* root);
    std::vector<Person*> Search(std::string &val);
    virtual void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) = 0;
};
// Implement a parent RBTree class and have all the categories of RBTrees
// inherit from it and overide search, insert, delete.

class IDRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
};
class FNRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
};
class LNRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
};
class ORIRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
};
class DESRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
};
class BDRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
};