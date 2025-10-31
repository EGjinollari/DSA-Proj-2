#pragma once
#include "node.h"
#include <vector>

class RBTree {
    private:
    Node* root = nullptr;
    std::vector<int> taken_ids;
    
    public:

    RBTree(Node* root);
    ~RBTree();
    void Deletion_Helper(Node* root);
    std::vector<Person*> Search(std::string &val);
    virtual void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) = 0;
    
    void Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest);
    virtual Node* Insert_Helper(Node* root, Person* p, std::string val) = 0;
};
// Implement a parent RBTree class and have all the categories of RBTrees
// inherit from it and overide search, insert, delete.

class IDRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p, std::string val) override;
};
class FNRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p,std::string val) override;
};
class LNRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p, std::string val) override;
};
class ORIRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p, std::string val) override;
};
class DESRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p, std::string val) override;
};
class BDRBTree: public RBTree {
    public:
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p, std::string val) override;
};

/*
TODO:
Search X
Insert X
Delete
Balance


*/