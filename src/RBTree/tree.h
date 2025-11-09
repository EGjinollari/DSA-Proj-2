#pragma once
#include "node.h"
#include <vector>
#include <unordered_set>
class RBTree {
    protected:
    Node* root = nullptr;
    std::unordered_set<int> taken_ids;
    
    public:
    Node* get_root();
    RBTree(Node* root);
    virtual ~RBTree();

    void Delete(Person* target);
    virtual Node* Delete_Helper(Node* root, Person* target, Node*& successor, bool& color) = 0;
    void Destructor_Helper(Node* root);

    std::vector<Person*> Search(std::string &val);
    virtual void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) = 0;
    
    virtual void Insert(Person* p) = 0;
    virtual Node* Insert_Helper(Node* root, Person* p, Node*& newNode) = 0;

    void InsertBalance(Node* node);
    void DeleteBalance(Node* node);
    void LRotate(Node* root);
    void RRotate(Node* root);

};