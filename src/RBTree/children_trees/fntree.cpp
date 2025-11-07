#include "fntree.h"

FNRBTree::FNRBTree() : RBTree(nullptr){}

void FNRBTree::Search_Helper(Node* root, std::vector<Person*> &vec, std::string val){
    if (!root) {
        return;
    }
    if (root->get_data()->get_first() == val) {
        vec.push_back(root->get_data());
    }
    Search_Helper(root->left, vec, val);
    Search_Helper(root->right, vec, val);
}

Node* FNRBTree::Insert_Helper(Node* root, Person* p, std::string val, Node*& newNode){
    if (!root){
        Node* n = new Node(p);
        n->flip_color();
        newNode = n;
        return n;
    }
    if (root->get_data()->get_first() < val){
        Node* rChild = Insert_Helper(root->right, p, val, newNode);
        root->right = rChild;
        rChild->parent = root;
    }else{  
        Node* lChild = Insert_Helper(root->left, p, val, newNode);
        root->left = lChild;
        lChild->parent = root;
    } 
    return root;
}

Node* FNRBTree::Delete_Helper(Node* root, std::string target, Node*& successor, bool& color) {
    if (!root) return nullptr;

    std::string curr = root->get_data()->get_first();
    if (target < curr)
        root->left = Delete_Helper(root->left, target, successor, color);
    else if (target > curr)
        root->right = Delete_Helper(root->right, target, successor, color);
    else {
        color = root->color;
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        } 
        else if (!root->left) {
           Node* temp = root->right;
            temp->parent = root->parent;
            successor = temp;
            delete root;
            return temp;
        } 
        else if (!root->right) {
            Node* temp = root->left;
            temp->parent = root->parent;
            successor = temp;
            delete root;
            return temp;
        } 
        else {
            Node* succ = root->right;
            while (succ->left) succ = succ->left;
            root->set_data(succ->get_data());
            root->right = Delete_Helper(root->right, succ->get_data()->get_first(), successor, color);
        }
    }
    return root;
}