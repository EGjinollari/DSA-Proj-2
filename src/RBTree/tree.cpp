#include "tree.h"
#include "node.h"
Node* RBTree::get_root(){
    return this->root;
}


RBTree::RBTree(Node* root){
    this->root = root;
}

void RBTree::Destructor_Helper(Node* root){
    if (!root){
        return;
    }

    Destructor_Helper(root->left);
    Destructor_Helper(root->right);
    delete root;
}

RBTree::~RBTree(){
    Destructor_Helper(root);
}

std::vector<Person*> RBTree::Search(std::string &name)  {
    std::vector<Person*> vec;
    Search_Helper(root, vec, name);
    return vec;
}
void RBTree::DeleteBalance(Node* node) {
    while (node != root && (node == nullptr || node->color == 0)) {
        Node* p = node->parent;
        if (node == p->left) {
            Node* u = p->right;
            if (u && u->color == 1) {
                u->flip_color();
                p->flip_color();
                LRotate(p);
                u = p->right;
            }
            if ((!u->left || u->left->color == 0) && (!u->right || u->right->color == 0)) {
                if (u) {
                    u->flip_color();
                }
                node = p;
            } 
            else {
                if (!u->right || u->right->color == 0) {
                    if (u->left) {
                        u->left->flip_color();
                    }
                    u->flip_color();
                    RRotate(u);
                    u = p->right;
                }
                u->color = p->color;
                p->color = 0;
                if (u->right) {
                    u->right->color = 0;
                }
                LRotate(p);
                node = root;
            }
        } 
        else {
            Node* u = p->left;
            if (u && u->color == 1) {
                u->flip_color();
                p->flip_color();
                RRotate(p);
                u = p->left;
            }
            if ((!u->right || u->right->color == 0) && (!u->left || u->left->color == 0)) {
                if (u) {
                    u->flip_color();
                }
                node = p;
            } 
            else {
                if (!u->left || u->left->color == 0) {
                    if (u->right){ 
                        u->right->flip_color();
                    }
                    u->flip_color();
                    LRotate(u);
                    u = p->left;
                }
                u->color = p->color;
                p->color = 0;
                if (u->left){ 
                    u->left->color = 0;
                }
                RRotate(p);
                node = root;
            }
        }
    }
    if (node) {
        node->color = 0;
    }
}


void RBTree::InsertBalance(Node* node){
    Node* p = nullptr;
    Node* gp = nullptr;

    while((node != root) && (node->color == 1) && (node->parent->color == 1)){
        p = node->parent;
        gp = p->parent;
        if (!gp){break;}

        if (p == gp->left){
            Node* u = gp->right;

            if (u != nullptr && u->color == 1){
                gp->flip_color();
                p->flip_color();
                u->flip_color();
                node = gp;
            }
            else{
                if (node == p->right) {
                    LRotate(p);
                    node = p;
                    p = node->parent;
                }
                RRotate(gp);
                int temp = p->color;
                p->color = gp->color;
                gp->color = temp;
                node = p;
            }
        }
        else{
            Node* u = gp->left;

            if (u != nullptr && u->color == 1){
                gp->flip_color();
                p->flip_color();
                u->flip_color();
                node = gp;
            }
            else{
                if (node == p->left){
                    RRotate(p);
                    node = p;
                    p = node->parent;
                }
                LRotate(gp);
                int temp = p->color;
                p->color = gp->color;
                gp->color = temp;
                node = p;
            }
        }
    }
    while(node->parent != nullptr){
        node = node->parent;
    }
    root = node;
    root->color = 0;

}


void RBTree::Delete(Node* root, std::string target){
    Node* node = nullptr;
    bool color = 1;
    root = Delete_Helper(root, target, node, color);
    if (color == 0 && node){
        DeleteBalance(node);
    }
    if (root){
        root->color = 0;
    }
}

void RBTree::LRotate(Node* root){
    Node* right = root->right;
    root->right = right->left;
    if (right-> left != nullptr){
        right->left->parent = root;
    }
    right->parent = root->parent;
    if(root->parent == nullptr){
        this->root = right;
    }
    else if (root == root->parent->left){
        root->parent->left = right;
    }
    else{
        root->parent->right = right;
    }
    right->left = root;
    root->parent = right;

}

void RBTree::RRotate(Node* root){
    Node* left = root->left;
    root->left = left->right;
    if (left-> right != nullptr){
        left->right->parent = root;
    }
    left->parent = root->parent;
    if(root->parent == nullptr){
        this->root = left;
    }
    else if (root == root->parent->right){
        root->parent->right = left;
    }
    else{
        root->parent->left = left;
    }
    left->right = root;
    root->parent = left;
}
