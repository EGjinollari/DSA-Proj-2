#pragma once
#include <vector>
#include <string>

class BTreeNode{
    private:
    std::vector<std::string> keys;
    int min_degree;
    std::vector<BTreeNode*> children;
    int num_of_keys;
    bool leaf;

    public:

    virtual void insert_non_full(std::string val) = 0;
    void split(int i, BTreeNode* child);
    void traverse();
    virtual BTreeNode* search(std::string val) = 0;

    std::vector<std::string>& get_keys();
    int get_min_degree();
    std::vector<BTreeNode*>& get_children();
    int get_num_of_keys();
    bool is_leaf();

};

