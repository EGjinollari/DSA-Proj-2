#pragma once
#include "../tree.h"

class ORIRBTree: public RBTree {
    public:
    ORIRBTree();
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p, std::string val) override;
    Node* Delete_Helper(Node* root, std::string target, Node*& successor, bool& color) override;
};