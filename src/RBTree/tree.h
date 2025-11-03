#pragma once
#include "node.h"
#include <vector>

class RBTree {
    private:
    Node* root = nullptr;
    std::vector<int> taken_ids;
    
    public:
    Node* get_root();
    RBTree(Node* root);
    ~RBTree();

    void Delete(Node* root, std::string target);
    virtual Node* Delete_Helper(Node* root, std::string target, Node*& successor, bool& color) = 0;
    void Destructor_Helper(Node* root);

    std::vector<Person*> Search(std::string &val);
    virtual void Search_Helper(Node* root, std::vector<Person*> &vec, std::string val) = 0;
    
    void Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest);
    virtual Node* Insert_Helper(Node* root, Person* p, std::string val) = 0;

    void InsertBalance(Node* node);
    void DeleteBalance(Node* node);
    void LRotate(Node* root);
    void RRotate(Node* root);

};

/*
TODO:
Search X
Insert X
Delete X
Balance
Link all the trees together

*/