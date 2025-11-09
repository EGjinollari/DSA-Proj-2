#pragma once
#include "../tree.h"
// Child tree that sorts by destination
class DESRBTree: public RBTree {
    public:
    DESRBTree();
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Delete_Helper(Node* root, Person* target, Node*& successor, bool& color) override;
    Node* Insert_Helper(Node* root, Person* p, Node*& newNode) override;
    void Insert(Person* p) override;
};