#include "oritree.h"

ORIRBTree::ORIRBTree() : RBTree(nullptr){}

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

void ORIRBTree::Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest){
    {
        if (taken_ids.count(id)) {
        return;
        }

        Person* p = new Person(id, fn, ln, bday, origin, dest);
        Node* new_node = nullptr;
        root = Insert_Helper(root, p, origin, new_node);
        if (new_node) {
            InsertBalance(new_node);
            taken_ids.insert(id);
            
        }

    }
}

Node* ORIRBTree::Insert_Helper(Node* root, Person* p, std::string val, Node*& newNode){
    if (!root){
        Node* n = new Node(p);
        newNode = n;
        return n;
    }
    if (root->get_data()->get_origin() < val){
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

Node* ORIRBTree::Delete_Helper(Node* root, std::string target, Node*& successor, bool& color) {
    if (!root) return nullptr;

    std::string curr = root->get_data()->get_origin();
    if (target < curr)
        root->left = Delete_Helper(root->left, target, successor, color);
    else if (target > curr)
        root->right = Delete_Helper(root->right, target, successor, color);
    else {
        taken_ids.erase(std::stoi(root->get_data()->get_id()));
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