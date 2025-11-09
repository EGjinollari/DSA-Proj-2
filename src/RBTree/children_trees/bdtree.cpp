#include "bdtree.h"

BDRBTree::BDRBTree() : RBTree(nullptr){}

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

void BDRBTree::Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest){
    {
        if (taken_ids.count(id)) {
        return;
        }

        Person* p = new Person(id, fn, ln, bday, origin, dest);
        Node* new_node = nullptr;
        root = Insert_Helper(root, p, std::to_string(bday), new_node);
        if (new_node) {
            InsertBalance(new_node);
            taken_ids.insert(id);
            
        }

    }
}


Node* BDRBTree::Insert_Helper(Node* root, Person* p, std::string val, Node*& newNode){
    if (!root){
        Node* n = new Node(p);
        newNode = n;
        return n;
    }
    if (stoi(root->get_data()->get_birthday()) < stoi(val)){
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

Node* BDRBTree::Delete_Helper(Node* root, Person* target, Node*& successor, bool& color) {
    if (!root){
        return nullptr;
    }

    if (root->person == target){

        taken_ids.erase(std::stoi(root->get_data()->get_id()));
        color = root->color;

        if (!root->left && !root->right){
            successor = root->parent;
            delete root;
            return nullptr;
        }

        if (!root->left){
            Node* temp = root->right;
            temp->parent = root->parent;
            successor = temp;
            delete root;
            return temp;
        }
        if (!root->right){
            Node* temp = root->left;
            temp->parent = root->parent;
            successor = temp;
            delete root;
            return temp;
        }
        
        Node* succ = root->right;
        while (succ->left){
            succ = succ->left;
        }

        Person* temp = root->person;
        root->person = succ->person;
        succ->person = temp;

        root->right = Delete_Helper(root->right, temp, successor, color);
        if (root->right){
            root->right->parent = root;
        }
        return root;
    }

    int curr = stoi(root->get_data()->get_birthday());
    if (stoi(target->get_birthday()) < curr){
        root->left = Delete_Helper(root->left, target, successor, color);
        if (root->left){
            root->left->parent = root;
        }
    }
    else{
        root->right = Delete_Helper(root->right, target, successor, color);
        if (root->right){
            root->right->parent = root;
        }
    }

    return root;
    
}