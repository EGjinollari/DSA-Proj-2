#include "destree.h"

DESRBTree::DESRBTree() : RBTree(nullptr){}

void DESRBTree::Search_Helper(Node* root, std::vector<Person*> &vec, std::string val){
    if (!root) {
        return;
    }
    if (root->get_data()->get_destination() == val) {
        vec.push_back(root->get_data());
    }
    Search_Helper(root->left, vec, val);
    Search_Helper(root->right, vec, val);
}

void DESRBTree::Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest){
    {
        if (taken_ids.count(id)) {
        return;
        }

        Person* p = new Person(id, fn, ln, bday, origin, dest);
        Node* new_node = nullptr;
        root = Insert_Helper(root, p, dest, new_node);
        if (new_node) {
            InsertBalance(new_node);
            taken_ids.insert(id);
            
        }

    }
}

Node* DESRBTree::Insert_Helper(Node* root, Person* p, std::string val, Node*& newNode){
    if (!root){
        Node* n = new Node(p);
        newNode = n;
        return n;
    }
    if (root->get_data()->get_destination() < val){
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

Node* DESRBTree::Delete_Helper(Node* root, std::string target, Node*& successor, bool& color) {
    if (!root) return nullptr;

    std::string curr = root->get_data()->get_destination();
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
            temp->parent = root->parent;
            successor = temp;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            temp->parent = root->parent;
            successor = temp;
            delete root;
            return temp;
        } else {
            Node* succ = root->right;
            while (succ->left) succ = succ->left;
            root->set_data(succ->get_data());
            root->right = Delete_Helper(root->right, succ->get_data()->get_destination(), successor, color);
        }
    }
    return root;
}