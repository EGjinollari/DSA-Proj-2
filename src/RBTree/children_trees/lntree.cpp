#include "lntree.h"

LNRBTree::LNRBTree() : RBTree(nullptr){}

// Recurisvely search for a given last name
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

// Insert a person by last name (wraps insert_helper)
void LNRBTree::Insert(Person* p){
    {
        if (taken_ids.count(stoi(p->get_id()))) {
        return;
        }

        Node* new_node = nullptr;
        root = Insert_Helper(root, p, new_node);
        if (new_node) {
            InsertBalance(new_node);
            taken_ids.insert((stoi(p->get_id())));
            
        }

    }
}

// Recursively locates where to insert node and inserts
Node* LNRBTree::Insert_Helper(Node* root, Person* p, Node*& newNode){
    if (!root){
        Node* n = new Node(p);
        newNode = n;
        return n;
    }
    if (root->get_data()->get_last() < p->get_last()){
        Node* rChild = Insert_Helper(root->right, p, newNode);
        root->right = rChild;
        rChild->parent = root;
    }else{  
        Node* lChild = Insert_Helper(root->left, p, newNode);
        root->left = lChild;
        lChild->parent = root;
    } 
    return root;
}

// Recurisvely find and delete from the last name tree
Node* LNRBTree::Delete_Helper(Node* root, Person* target, Node*& successor, bool& color) {
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

        Person* temp = succ->person;
        root->person = succ->person;

        root->right = Delete_Helper(root->right, temp, successor, color);
        if (root->right){
            root->right->parent = root;
        }
        return root;
    }

    std::string curr = root->get_data()->get_last();
    if (target->get_last() < curr){
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
