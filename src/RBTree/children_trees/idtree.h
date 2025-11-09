#pragma once
#include <vector>
#include "../tree.h"

class IDRBTree: public RBTree {
    public:
    IDRBTree();
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Delete_Helper(Node* root, Person* target, Node*& successor, bool& color) override;
    Node* Insert_Helper(Node* root, Person* p, Node*& newNode) override;
    void Insert(Person* p) override;
};