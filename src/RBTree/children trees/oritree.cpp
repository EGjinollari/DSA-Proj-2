#include "oritree.h"

void ORIRBTree::Search_Helper(Node* root, std::vector<Person*> &vec, std::string val){
    if (!root) {
        return;
    }
    if (root->get_data()->get_origin() == val) {
        vec.push_back(root->get_data());
    }
    Search_Helper(root->left, vec, val);
    Search_Helper(root->right, vec, val);

}

Node* ORIRBTree::Insert_Helper(Node* root, Person* p, std::string val){
    if (!root){
        Node* n = new Node(p);
        return n;
    }
    if (root->get_data()->get_origin() < val){
        Node* rChild = Insert_Helper(root->right, p, val);
        root->right = rChild;
        rChild->parent = root;
    }else{  
        Node* lChild = Insert_Helper(root->left, p, val);
        root->left = lChild;
        lChild->parent = root;
    } 
    return root;
}

Node* ORIRBTree::Delete_Helper(Node* root, std::string target, Node*& successor, bool& color) {
    if (!root) return nullptr;

    std::string curr = root->get_data()->get_origin();
    if (target < curr)
        root->left = Delete_Helper(root->left, target, successor, color);
    else if (target > curr)
        root->right = Delete_Helper(root->right, target, successor, color);
    else {
        color = root->color;
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        } else if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* succ = root->right;
            while (succ->left) succ = succ->left;
            root->set_data(succ->get_data());
            root->right = Delete_Helper(root->right, succ->get_data()->get_origin(), successor, color);
        }
    }
    return root;
}