#pragma once
#include <vector>
#include "../tree.h"

class IDRBTree: public RBTree {
    public:
    IDRBTree();
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p, std::string val, Node*& newNode) override;
    Node* Delete_Helper(Node* root, std::string target, Node*& successor, bool& color) override;
};