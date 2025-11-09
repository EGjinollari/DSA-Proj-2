#pragma once
#include <vector>
#include "../tree.h"

class BDRBTree: public RBTree {
    public:
    BDRBTree();
    void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) override;
    Node* Insert_Helper(Node* root, Person* p, std::string val, Node*& newNode) override;
    Node* Delete_Helper(Node* root, Person* target, Node*& successor, bool& color) override;
    void Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest) override;
};


    
   