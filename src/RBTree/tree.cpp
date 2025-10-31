#include "tree.h"
#include "node.h"


RBTree::RBTree(Node* root){
    this->root = root;
}

void RBTree::Deletion_Helper(Node* root){
    if (!root){
        return;
    }

    Deletion_Helper(root->left);
    Deletion_Helper(root->right);
    delete root;
}

RBTree::~RBTree(){
    Deletion_Helper(root);
}

std::vector<Person*> RBTree::Search(std::string &name)  {
    std::vector<Person*> vec;
    Search_Helper(root, vec, name);
    return vec;
}

void RBTree::Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest){
    bool unique = true;
    for (auto i: taken_ids){
        if (i = id){
            unique = false;
            break;
        }
    }

    if (unique){
        Person* p = new Person(id, fn, ln, bday, origin, dest);
        root = Insert_Helper(root, p, std::to_string(id));
    }

}

// ID Tree

void IDRBTree::Search_Helper(Node* root, std::vector<Person*> &vec, std::string val){
    if (!root) {
        return;
    }
    if (root->get_data()->get_id() == val) {
        vec.push_back(root->get_data());
    }
    Search_Helper(root->left, vec, val);
    Search_Helper(root->right, vec, val);
}

Node* IDRBTree::Insert_Helper(Node* root, Person* p, std::string val){
    if (!root){
        return new Node(p);
    }
    if (stoi(root->get_data()->get_id()) < stoi(val)){
        root->right = Insert_Helper(root->right, p, val);
    }else{
        root->left = Insert_Helper(root->left, p, val);
    } 
}

// BD Tree


void BDRBTree::Search_Helper(Node* root, std::vector<Person*> &vec, std::string val){
    if (!root) {
        return;
    }
    if (root->get_data()->get_birthday() == val) {
        vec.push_back(root->get_data());
    }
    Search_Helper(root->left, vec, val);
    Search_Helper(root->right, vec, val);
}

Node* BDRBTree::Insert_Helper(Node* root, Person* p, std::string val){
    if (!root){
        return new Node(p);
    }
    if (stoi(root->get_data()->get_birthday()) < stoi(val)){
        root->right = Insert_Helper(root->right, p, val);
    }else{
        root->left = Insert_Helper(root->left, p, val);
    } 
}

// First Name Tree

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

Node* FNRBTree::Insert_Helper(Node* root, Person* p, std::string val){
    if (!root){
        return new Node(p);
    }
    if (root->get_data()->get_first() < val){
        root->right = Insert_Helper(root->right, p, val);
    }else{
        root->left = Insert_Helper(root->left, p, val);
    } 
}

// Last Name Tree
void LNRBTree::Search_Helper(Node* root, std::vector<Person*> &vec, std::string val){
    if (!root) {
        return;
    }
    if (root->get_data()->get_last() == val) {
        vec.push_back(root->get_data());
    }
    Search_Helper(root->left, vec, val);
    Search_Helper(root->right, vec, val);
}

Node* LNRBTree::Insert_Helper(Node* root, Person* p, std::string val){
    if (!root){
        return new Node(p);
    }
    if (root->get_data()->get_last() < val){
        root->right = Insert_Helper(root->right, p, val);
    }else{
        root->left = Insert_Helper(root->left, p, val);
    } 
}

// Origin Tree

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
        return new Node(p);
    }
    if (root->get_data()->get_origin() < val){
        root->right = Insert_Helper(root->right, p, val);
    }else{
        root->left = Insert_Helper(root->left, p, val);
    } 
}
// Destination Tree

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

Node* FNRBTree::Insert_Helper(Node* root, Person* p, std::string val){
    if (!root){
        return new Node(p);
    }
    if (root->get_data()->get_destination() < val){
        root->right = Insert_Helper(root->right, p, val);
    }else{
        root->left = Insert_Helper(root->left, p, val);
    } 
}

